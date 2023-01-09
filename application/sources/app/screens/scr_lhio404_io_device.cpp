#include "scr_lhio404_io_device.h"

static void view_scr_lhio404_io_device();

view_dynamic_t dyn_view_item_lhio404_io_device = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_lhio404_io_device
};

view_screen_t scr_lhio404_io_device = {
	&dyn_view_item_lhio404_io_device,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void view_scr_lhio404_io_device() {
	char str[4];
	
	view_render.clear();
	view_render.drawRect(0, 0, 128, 64, WHITE);
	view_render.fillRoundRect(0, 0, 42, 14, 1, WHITE);

	view_render.setTextSize(1);
	view_render.setTextColor(BLACK);
	view_render.setCursor(8, 4);
	view_render.print("RELAY");

	view_render.drawRect(4  , 36, 24, 16, WHITE);
	view_render.drawRect(36 , 36, 24, 16, WHITE);
	view_render.drawRect(68 , 36, 24, 16, WHITE);
	view_render.drawRect(100, 36, 24, 16, WHITE);

	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);

	for (uint16_t regIndex = 4; regIndex < MB_LHIO404_IO_Device.listRegAmount; ++regIndex) {
		xsprintf(str, "IN%d", regIndex - 3);
		view_render.setCursor(8 + 32 * (regIndex - 4), 26);
		view_render.print(str);
		if (MB_LHIO404_IO_Device.listRegDevice[regIndex].regValue == 1) {
			view_render.setCursor(10 + 32 * (regIndex - 4), 40);
			view_render.print("ON");
		}
		else {
			view_render.setCursor(8 + 32 * (regIndex - 4), 40);
			view_render.print("OFF");
		}
	}

	view_render.update();
}

void scr_lhio404_io_device_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");

		timer_set(AC_TASK_DISPLAY_ID, \
				  AC_DISPLAY_SHOW_MODBUS_PULL_UPDATE, \
				  AC_DISPLAY_SHOW_MODBUS_PULL_INTERVAL, \
				  TIMER_PERIODIC);

		timer_set(AC_TASK_DISPLAY_ID, \
				  AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP, \
				  AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP_INTERVAL, \
				  TIMER_ONE_SHOT);
	}
		break;

	case AC_DISPLAY_SHOW_MODBUS_PULL_UPDATE: {
		updateDataModbusDevice(&MB_LHIO404_IO_Device);
	}
		break;

	case AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_MODBUS_PULL_SLEEP\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_MODBUS_PULL_UPDATE);
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_MODBUS_PULL_UPDATE);
		SCREEN_TRAN(scr_es35sw_th_sensor_handle, &scr_es35sw_th_sensor);
	}
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		BUZZER_PlayTones(tones_3beep);
	}
		break;

	default:
		break;
	}
}
