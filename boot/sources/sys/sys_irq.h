#ifndef __SYS_IRQ_H__
#define __SYS_IRQ_H__

#ifdef __cplusplus
extern "C"
{
#endif

extern void sys_irq_nrf24l01();
extern void sys_irq_shell();
extern void sys_irq_ir_io_rev();
extern void sys_irq_timer_50us();
extern void sys_irq_timer_10ms();
extern void sys_irq_timer_hs1101();

#ifdef __cplusplus
}
#endif

#endif // __SYS_IRQ_H__
