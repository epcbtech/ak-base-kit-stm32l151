/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   26/08/2019
 * @brief:  system thread service
 ******************************************************************************
**/
#ifndef __SYS_THREAD__
#define __SYS_THREAD__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/* Thread Control Block */
typedef struct {
	void* sp;
} sys_thread_t;

typedef void (*sys_thread_start_routine)();

extern void sys_thread_create(sys_thread_t* __sys_thread,
					   sys_thread_start_routine __sys_thread_start_routine,
					   void* __sp, uint32_t __sp_size);

extern void sys_thread_run();

extern void sys_thread_sheduler();

#ifdef __cplusplus
}
#endif

#endif //__SYS_THREAD__
