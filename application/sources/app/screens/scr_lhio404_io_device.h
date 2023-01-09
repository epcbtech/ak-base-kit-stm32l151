#ifndef __SCR_LHIO404_IO_DEVICE_H__
#define __SCR_LHIO404_IO_DEVICE_H__

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

extern view_dynamic_t dyn_view_item_lhio404_io_device;

extern view_screen_t scr_lhio404_io_device;
extern void scr_lhio404_io_device_handle(ak_msg_t* msg);

#endif //__SCR_LHIO404_IO_DEVICE_H__
