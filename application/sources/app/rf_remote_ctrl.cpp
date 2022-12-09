/**
 ******************************************************************************
 * @author: GaoKong
 * @date:   23/11/2016
 ******************************************************************************
**/

#include <stdint.h>

#include "ak.h"
#include "task.h"
#include "timer.h"
#include "message.h"

#include "cmd_line.h"
#include "xprintf.h"

#include "sys_ctrl.h"
#include "sys_io.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_data.h"

void rf_printf(uint8_t* buf, uint32_t len) {
	(void)buf;
	(void)len;
}
