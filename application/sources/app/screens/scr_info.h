#ifndef __SCR_INFO_H__
#define __SCR_INFO_H__

#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"
#include "task_list.h"
#include "task_display.h"
#include "view_render.h"

#include "buzzer.h"

extern view_dynamic_t dyn_view_info;

extern view_screen_t scr_info;
extern void scr_info_handle(ak_msg_t* msg);

#endif //__SCR_INFO_H__
