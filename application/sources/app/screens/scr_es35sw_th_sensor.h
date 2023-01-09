#ifndef __SCR_ES35SW_TH_SENSOR_H__
#define __SCR_ES35SW_TH_SENSOR_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "app_modbus_pull.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

extern view_dynamic_t dyn_view_item_es35sw_th_sensor;

extern view_screen_t scr_es35sw_th_sensor;
extern void scr_es35sw_th_sensor_handle(ak_msg_t* msg);

#endif //__SCR_ES35SW_TH_SENSOR_H__
