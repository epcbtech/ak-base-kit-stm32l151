#ifndef __KALMAN_H__
#define __KALMAN_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

extern uint16_t kalman_filter(uint16_t signal_in);

#ifdef __cplusplus
}
#endif

#endif //__KALMAN_H__
