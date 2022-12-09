#ifndef __IR_H__
#define __IR_H__

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>

/* IR driver return */
#define IR_DRIVER_OK            (0x00)
#define IR_DRIVER_NG            (0x01)

/* IR buffer define */
#define MIN_RAW_LEN               (12)
#define MAX_RAW_LEN               (450)

/* IR time&interrupt define */
#define IR_IRQ_POLLING_INTERVAL   (1)  /* unit 50us */
#define IR_IRQ_FINISH_TIME        (1000)

/* IR decode result code */
#define IR_DECODE_SUCCESS       (0x01)
#define IR_DECODE_ERR_REV       (0x02)
#define IR_DECODE_ERR_LEN       (0x03)

/* IR state */
#define IR_STATE_IDLE           (0x00)
#define IR_STATE_DECODE_EN      (0x01)
#define IR_STATE_DECODING       (0x02)
#define IR_STATE_SENDING        (0x03)

/* IR bit state */
#define IR_BIT_STATE_GET_COUNTER_DISABLE      (0x01)
#define IR_BIT_STATE_GET_COUNTER_ENABLE       (0x02)

typedef void (*pf_decode_callback)(void*);

typedef struct {
	pf_decode_callback  decode_callback;

	uint8_t     decode_result;

	uint8_t     state;

	uint8_t     bit_state;
	uint32_t    bit_len;

	uint16_t    irq_counter;

	uint16_t    buf[MAX_RAW_LEN];
} ir_t;

extern void     ir_init(ir_t* ir);
extern uint8_t  ir_decode_callback_register(ir_t* ir, pf_decode_callback callback_func);
extern uint8_t  ir_decode_start(ir_t* ir);
extern void		ir_decode_exit();
extern void     ir_decode_irq_timer_polling(ir_t* ir);
extern void     ir_decode_irq_rev_io_polling(ir_t* ir);
extern uint8_t  ir_send_rawdata(ir_t* ir, uint16_t* buf, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif //__IR_H__
