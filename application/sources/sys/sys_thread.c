#include <stdint.h>

#include "platform.h"
#include "sys_thread.h"
#include "sys_io.h"

sys_thread_t* volatile sys_thread_current;
sys_thread_t* volatile sys_thread_next;

sys_thread_t* sys_thread[32 + 1];
uint8_t sys_thread_num;
uint8_t sys_thread_id;

void sys_thread_create(sys_thread_t* __sys_thread,
					   sys_thread_start_routine __sys_thread_start_routine,
					   void* __sp, uint32_t __sp_size) {

	uint32_t* _sp = (uint32_t*)((((uint32_t)__sp + __sp_size) / 8) * 8);
	uint32_t* _stack_limit;

	*(--_sp) = (1 << 24); /* xPSR */
	*(--_sp) = (uint32_t)__sys_thread_start_routine; /* PC */
	*(--_sp) = 0x0000000EU; /* LR */
	*(--_sp) = 0x0000000CU; /* R12 */
	*(--_sp) = 0x00000003U; /* R3 */
	*(--_sp) = 0x00000002U; /* R2 */
	*(--_sp) = 0x00000001U; /* R1 */
	*(--_sp) = 0x00000000U; /* R0 */
	/* R11-R4 */
	*(--_sp) = 0x0000000BU; /* R11 */
	*(--_sp) = 0x0000000AU; /* R10 */
	*(--_sp) = 0x00000009U; /* R9 */
	*(--_sp) = 0x00000008U; /* R8 */
	*(--_sp) = 0x00000007U; /* R7 */
	*(--_sp) = 0x00000006U; /* R6 */
	*(--_sp) = 0x00000005U; /* R5 */
	*(--_sp) = 0x00000004U; /* R4 */

	__sys_thread->sp = _sp;

	_stack_limit = (uint32_t*)(((((uint32_t)__sp - 1U) / 8) + 1U) * 8);

	for (_sp = _sp - 1U; _sp >= _stack_limit; --_sp) {
		*_sp = 0xDEADBEEFU;
	}

	sys_thread[sys_thread_num] = __sys_thread;
	++sys_thread_num;
}

void sys_thread_run() {
	ENTRY_CRITICAL();
	sys_thread_sheduler();
	EXIT_CRITICAL();
}

void sys_thread_sheduler() {
	++sys_thread_id;
	if (sys_thread_id == sys_thread_num) {
		sys_thread_id = 0U;
	}
	sys_thread_next = sys_thread[sys_thread_id];

	if (sys_thread_next != sys_thread_current) {
		SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	}
}
