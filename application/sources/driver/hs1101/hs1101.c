#include "hs1101.h"

#include "port.h"
#include "app_dbg.h"

#include "sys_io.h"
#include "sys_ctrl.h"

void hs1101_init(hs1101_t * hs1101, uint16_t sample) {
	hs1101->trigger_time	= 0;
	hs1101->sum_time		= 0;
	hs1101->capacitance		= 0;
	hs1101->error			= 0;
	hs1101->sample			= sample;
	hs1101->number_capture	= 0;
	hs1101->relative_humidity = 0;

	io_hs1101_read_enable();
}

uint8_t hs1101_read(hs1101_t * hs1101) {
	hs1101->trigger_time = io_timer4_get_capture();

	sys_ctrl_delay_ms(20);

	hs1101->capacitance = (hs1101->trigger_time * 32) / RES;

	hs1101->relative_humidity = (100 * hs1101->capacitance - 16300) / 37;

	if (hs1101->capacitance < 163) {
		hs1101->relative_humidity = RH_MIN;
	}
	else if (hs1101->capacitance > 200) {
		hs1101->relative_humidity = RH_MAX;
	}

	return hs1101->relative_humidity;
}

void hs1101_irq_timer_polling(hs1101_t * hs1101) {
	hs1101->trigger_time = io_timer4_get_capture();
}
