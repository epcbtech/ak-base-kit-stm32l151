#include "rtc.h"
#include "../../ak/port.h"
#include "../sys/sys_dbg.h"

uint8_t rtc_init(rtc_t* rtc, pf_rtc_ctrl init, \
				 pf_rtc_time_ctrl set_time,\
				 pf_rtc_time_ctrl get_time,\
				 pf_rtc_time_ctrl set_alarm,\
				 pf_rtc_time_ctrl get_alarm) {
	if (init) {
		rtc->init = init;
		rtc->init();
	}
	else {
		return DRIVER_RTC_NG;
	}

	if (set_time) {
		rtc->set_time = set_time;
	}
	else {
		return DRIVER_RTC_NG;
	}

	if (get_time) {
		rtc->get_time = get_time;
	}
	else {
		return DRIVER_RTC_NG;
	}

	if (set_alarm) {
		rtc->set_alarm = set_alarm;
	}
	else {
		return DRIVER_RTC_NG;
	}

	if (get_alarm) {
		rtc->get_alarm = get_alarm;
	}
	else {
		return DRIVER_RTC_NG;
	}

	return DRIVER_RTC_OK;
}

void rtc_set_time(rtc_t* rtc, rtc_time_t* time) {
	if (rtc->set_time) {
		rtc->set_time(time);
	}
}

void rtc_get_time(rtc_t* rtc, rtc_time_t* time) {
	if (rtc->get_time) {
		rtc->get_time(time);
	}
}

void rtc_set_alarm(rtc_t* rtc, rtc_time_t* time) {
	if (rtc->set_alarm) {
		rtc->set_alarm(time);
	}
}

void rtc_get_alarm(rtc_t* rtc, rtc_time_t* time) {
	if (rtc->get_alarm) {
		rtc->get_alarm(time);
	}
}
