#ifndef __APP_BSP_H__
#define __APP_BSP_H__

#define BUTTON_MODE_ID					(0x01)
#define BUTTON_UP_ID					(0x02)
#define BUTTON_DOWN_ID					(0x03)

extern button_t btn_mode;
extern button_t btn_up;
extern button_t btn_down;

extern void btn_mode_callback(void*);
extern void btn_up_callback(void*);
extern void btn_down_callback(void*);

#endif //__APP_BSP_H__
