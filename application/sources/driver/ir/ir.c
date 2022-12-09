#include "ir.h"

#include "port.h"

#include "sys_io.h"
#include "sys_ctrl.h"
#include "app_dbg.h"

#define IR_SEND_TIMEOUT			(100)	/* 100ms */

void ir_init(ir_t* ir) {
	ir->bit_len            = 0;
	ir->state              = IR_STATE_IDLE;

	memset(ir->buf, 0, MAX_RAW_LEN * sizeof(uint16_t));

	/* disable timer polling interrupt && receiver io interrupt */
	timer_50us_disable();
	ir_rev_io_irq_disable();
}

uint8_t ir_decode_callback_register(ir_t* ir, pf_decode_callback callback_func) {
	if (callback_func) {
		ir->decode_callback = callback_func;
		return IR_DRIVER_OK;
	}
	return IR_DRIVER_NG;
}

uint8_t ir_decode_start(ir_t* ir) {
	if (!(ir->decode_callback)) {
		return IR_DRIVER_NG;
	}

	ENTRY_CRITICAL();

	ir->bit_len     = 0;
	ir->state       = IR_STATE_DECODE_EN;
	ir->bit_state   = IR_BIT_STATE_GET_COUNTER_DISABLE;

	EXIT_CRITICAL();

	/* enable timer polling interrupt && receiver io interrupt */
	timer_50us_enable();
	ir_rev_io_irq_enable();

	return IR_DRIVER_OK;
}

void  ir_decode_exit() {
	/* disable timer polling interrupt && receiver io interrupt */
	timer_50us_disable();
	ir_rev_io_irq_disable();
}

void ir_decode_irq_timer_polling(ir_t* ir) {
	if ((ir->state == IR_STATE_DECODING)||(ir->state==IR_STATE_SENDING)){

		ir->irq_counter += IR_IRQ_POLLING_INTERVAL;     /* increase counter */
		if (ir->irq_counter >= IR_IRQ_FINISH_TIME) {   /* check finish decode */

			ENTRY_CRITICAL();

			/* disable timer polling interrupt && receiver io interrupt */
			timer_50us_disable();
			ir_rev_io_irq_disable();

			/* check decode success */
			if ((ir->bit_len > MIN_RAW_LEN) && (ir->bit_len < MAX_RAW_LEN)) {
				/* decode success */
				ir->decode_result = IR_DECODE_SUCCESS;
				ir->decode_callback((ir_t*)ir);
			}
			else {
				/* decode failed */
				ir->decode_result = IR_DECODE_ERR_REV;
				ir->decode_callback((ir_t*)ir);
			}

			/* change state to normal */
			ir->state = IR_STATE_IDLE;

			EXIT_CRITICAL();
		}
	}
}

void ir_decode_irq_rev_io_polling(ir_t* ir) {

	if (ir->state != IR_STATE_IDLE) {

		/* check first io interrupt */
		if (ir->bit_state == IR_BIT_STATE_GET_COUNTER_DISABLE) {

			ENTRY_CRITICAL();

			/* reset data */
			ir->irq_counter = 0;
			ir->bit_len     = 0;
			ir->state       = IR_STATE_DECODING;
			ir->bit_state   = IR_BIT_STATE_GET_COUNTER_ENABLE;

			EXIT_CRITICAL();
		}
		else {
			/* check buffer overfollow */
			if (ir->bit_len < MAX_RAW_LEN) {

				ENTRY_CRITICAL();

				ir->buf[ir->bit_len] = ir->irq_counter;     /* get new data */
				ir->irq_counter = 0;                        /* reset counter */

				EXIT_CRITICAL();

				ir->bit_len++;

			}
			else {
				/* decode fail */

				ENTRY_CRITICAL();

				/* disable timer polling interrupt && receiver io interrupt */
				timer_50us_disable();
				ir_rev_io_irq_disable();

				ir->decode_result = IR_DECODE_ERR_LEN;
				ir->state = IR_STATE_IDLE;
				ir->decode_callback((ir_t*)ir);

				EXIT_CRITICAL();
			}
		}

	}
}

uint8_t ir_send_rawdata(ir_t* ir, uint16_t* buf, uint32_t len) {
	uint32_t idx = 0;
	volatile uint32_t	current_timeout = 0;
	volatile uint32_t	current;
	volatile uint32_t	start = 0;

	if (len == 0 || buf == (uint16_t*)0 || ir->state != IR_STATE_IDLE) {
		return IR_DRIVER_NG;
	}

	/* enable send ir data */
	ir->state = IR_STATE_SENDING;   /* switch state to SENDING */
	ir->irq_counter = 0;            /* reset counter */
	timer_50us_enable();            /* enable timer polling */

	/* turn ON carrier frequency (first ir pulse) */
	ir_carrier_freq_on();

	start = sys_ctrl_millis();

	while (idx < len) {
		if (current_timeout >= IR_SEND_TIMEOUT) {
			/* disable send ir data */
			ir_carrier_freq_off();      /* ensure turn off carrier frequency */

			timer_50us_disable();       /* disable timer polling */
			ir->state = IR_STATE_IDLE;  /* switch state to IDLE */
			ir->irq_counter = 0;        /* reset counter */

			return IR_DRIVER_NG;
		}

		if (ir->irq_counter >= *(buf + idx)) {

			ENTRY_CRITICAL();

			/* reset counter */
			ir->irq_counter = 0;
			idx ++;

			if (idx & 0x01) {
				/* turn OFF carrier frequency */
				ir_carrier_freq_off();
			}
			else {
				/* turn ON carrier frequency */
				ir_carrier_freq_on();
			}

			/* reset timeout */
			current_timeout = 0;

			EXIT_CRITICAL();
		}

		/* check time-out */
		current = sys_ctrl_millis();

		if (current < start) {
			current_timeout += ((uint32_t)0xFFFFFFFF - start) + current;
		}
		else {
			current_timeout += current - start;
		}

		start = current;
	}

	/* disable send ir data */
	ir_carrier_freq_off();      /* ensure turn off carrier frequency */

	timer_50us_disable();       /* disable timer polling */
	ir->state = IR_STATE_IDLE;  /* switch state to IDLE */
	ir->irq_counter = 0;        /* reset counter */

	return IR_DRIVER_OK;
}
