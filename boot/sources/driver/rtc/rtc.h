#ifndef __RTC_H__
#define __RTC_H__
#include <stdint.h>

#define RTC_FORMAT_HOUR_24      (0x00)
#define RTC_FORMAT_HOUR_12      (0x01)

#define DRIVER_RTC_OK           (0x00)
#define DRIVER_RTC_NG           (0x01)

typedef struct {
	uint8_t hours;      /* 0 -> 12 && 0 -> 23 */
	uint8_t minutes;    /* 0 -> 59 */
	uint8_t seconds;    /* 0 -> 59 */
	uint8_t h12;        /* RTC_FORMAT_HOUR_24/RTC_FORMAT_HOUR_12 */
} rtc_time_t;

typedef void (*pf_rtc_ctrl)();
typedef void (*pf_rtc_time_ctrl)(rtc_time_t*);

typedef struct {
	rtc_time_t time;
	rtc_time_t alarm;
	pf_rtc_ctrl init;
	pf_rtc_time_ctrl set_time;
	pf_rtc_time_ctrl get_time;
	pf_rtc_time_ctrl set_alarm;
	pf_rtc_time_ctrl get_alarm;
} rtc_t;

extern uint8_t rtc_init(rtc_t* rtc, pf_rtc_ctrl init, \
						pf_rtc_time_ctrl set_time,\
						pf_rtc_time_ctrl get_time,\
						pf_rtc_time_ctrl set_alarm,\
						pf_rtc_time_ctrl get_alarm);

extern void rtc_set_time(rtc_t* rtc, rtc_time_t* time);
extern void rtc_get_time(rtc_t* rtc, rtc_time_t* time);
extern void rtc_set_alarm(rtc_t* rtc, rtc_time_t* time);
extern void rtc_get_alarm(rtc_t* rtc, rtc_time_t* time);

#endif //__RTC_H__
