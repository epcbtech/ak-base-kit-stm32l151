#ifndef __HS1101_H__
#define __HS1101_H__

#if defined (__cplusplus)
extern "C" {
#endif

#include <stdint.h>
#include <math.h>
#include <stdio.h>

#define RES				(100)

#define RH_MAX			(200)
#define RH_MIN			(0)

typedef struct {
	uint32_t	trigger_time;
	uint32_t	sum_time;
	uint16_t	capacitance;
	uint16_t	error;
	uint16_t	sample;
	uint16_t	number_capture;
	uint8_t		relative_humidity;
} hs1101_t;

extern void hs1101_init(hs1101_t*, uint16_t);
extern uint8_t hs1101_read(hs1101_t*);
extern void hs1101_irq_timer_polling(hs1101_t*);

#ifdef __cplusplus
}
#endif

#endif //__HS1101_H__
