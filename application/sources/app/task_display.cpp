#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "view_render.h"

#include "qrcode.h"

#include "app.h"
#include "app_dbg.h"

#include "task_list.h"
#include "task_display.h"

#if defined (TASK_BEEPER_EN)
#include "buzzer.h"
#endif

#include <math.h>
#include <vector>

using namespace std;

#define LCD_WIDTH			124
#define LCD_HEIGHT			60
#define AK_LOGO_AXIS_X		23
#define AK_LOGO_TEXT		(AK_LOGO_AXIS_X + 4)

#define MAX_BALL_DISPLAY	16

class ball {
	// rand from a to b
	// (rand() % (b - a + 1)) + a
public:
	static int total;
	int id, x, y, slope, axis_x, axis_y, radius;

	ball() {
		axis_x = 1;
		axis_y = 1;
		slope = (rand() % (31)) - 15;
		radius = (rand() % (7)) + 6;
		x = rand() % (LCD_WIDTH - radius);
		y = rand() % (LCD_HEIGHT - radius);
	}

	int distance(ball& __ball) {
		uint8_t dx, dy;
		dx = abs(x - __ball.x);
		dy = abs(y - __ball.y);
		return sqrt(dx*dx + dy*dy);
	}

	bool is_hit_to_other(ball& __ball) {
		if ((radius + __ball.radius) <= distance(__ball)) {
			return true;
		}
		else {
			return false;
		}
	}

	void moving() {
		if( axis_x > 0) {
			x = x + 2;
		}
		else {
			x = x - 2;
		}

		if (axis_y > 0) {
			y += 2 * atan(slope);
		}
		else {
			y -= 2 * atan(slope);
		}

		if (x > (LCD_WIDTH - radius) || x < radius) {
			axis_x = -axis_x;
			if (x < radius) {
				x = radius;
			}
		}

		if (y > (LCD_HEIGHT - radius) || y < radius ) {
			axis_y = -axis_y;
			if (y < radius) {
				y = radius;
			}
		}
	}
};

scr_mng_t scr_mng_app;

/* list of screen handler */
void view_scr_startup();
void scr_startup_handle(ak_msg_t* msg);

void view_scr_idle();
void scr_idle_handle(ak_msg_t* msg);

void view_scr_info();
void scr_info_handle(ak_msg_t* msg);

void view_scr_fw_updating();
void scr_fw_updating_handle(ak_msg_t* msg);

void ui_state_display_off(ak_msg_t* msg);

/**
 ******************************************************************************
 * objects MAIN SCREEN
 *
 ******************************************************************************
 */

/*----------[[[ITERM]]]------------*/
view_dynamic_t dyn_view_startup = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_startup
};

view_dynamic_t dyn_view_idle = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_idle
};

view_dynamic_t dyn_view_info = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_info
};

view_dynamic_t dyn_view_fw_updating = {
	{
		.item_type = ITEM_TYPE_DYNAMIC,
	},
	view_scr_fw_updating
};

/*----------[[[SCREEN]]]------------*/
view_screen_t scr_startup = {
	&dyn_view_startup,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

view_screen_t scr_idle = {
	&dyn_view_idle,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

view_screen_t scr_fw_updating = {
	&dyn_view_fw_updating,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

view_screen_t scr_info = {
	&dyn_view_info,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

view_screen_t scr_off = {
	ITEM_NULL,
	ITEM_NULL,
	ITEM_NULL,

	.focus_item = 0,
};

void task_display(ak_msg_t* msg) {
	scr_mng_dispatch(msg);
}

/*-------------- [[[ START UP SCREEN]]] ------------*/
void view_scr_startup() {
#define NUMFLAKES			10
#define XPOS				0
#define YPOS				1
#define DELTAY				2
#define LOGO16_GLCD_HEIGHT	16
#define LOGO16_GLCD_WIDTH	16

	/* ak logo */
	view_render.clear();
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(AK_LOGO_AXIS_X, 3);
	view_render.print("   __    _  _ ");
	view_render.setCursor(AK_LOGO_AXIS_X, 10);
	view_render.print("  /__\\  ( )/ )");
	view_render.setCursor(AK_LOGO_AXIS_X, 20);
	view_render.print(" /(__)\\ (   (");
	view_render.setCursor(AK_LOGO_AXIS_X, 30);
	view_render.print("(__)(__)(_)\\_)");
	view_render.setCursor(AK_LOGO_TEXT, 42);
	view_render.print("Active Kernel");
}

void scr_startup_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_INITIAL: {
		APP_DBG_SIG("AC_DISPLAY_INITIAL\n");
		view_render.initialize();
		view_render_display_on();
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_LOGO, AC_DISPLAY_STARTUP_INTERVAL, TIMER_ONE_SHOT);
	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE);
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;

	case AC_DISPLAY_SHOW_LOGO: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_LOGO\n");
		SCREEN_TRAN(scr_info_handle, &scr_info);
	}
		break;

	case AC_DISPLAY_SHOW_IDLE: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_IDLE\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;

	case AC_DISPLAY_SHOW_FW_UPDATE: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_FW_UPDATE\n");
		SCREEN_TRAN(scr_fw_updating_handle, &scr_fw_updating);
	}

	default:
		break;
	}
}

/*-------------- [[[ IDLE SCREEN]]] ------------*/
vector<ball> v_idle_ball;
int ball::total;

void view_scr_idle() {
	for(ball _ball : v_idle_ball) {
		view_render.drawCircle(_ball.x, _ball.y, _ball.radius, 144);
	}
}

void scr_idle_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		if (v_idle_ball.empty()) {
			ball new_ball;
			new_ball.id = ball::total++;
			v_idle_ball.push_back(new_ball);
		}

		timer_set(AC_TASK_DISPLAY_ID, \
				  AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE, \
				  AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE_INTERAL, \
				  TIMER_PERIODIC);
	}
		break;

	case AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE: {
		for (unsigned int i = 0; i < v_idle_ball.size(); i++) {
			v_idle_ball[i].moving();
		}
	}
		break;

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE);
		SCREEN_TRAN(ui_state_display_off, &scr_off);
	}
		break;

	case AC_DISPLAY_BUTON_UP_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_UP_RELEASED\n");
		ball new_ball;
		new_ball.id = ball::total++;

		if (v_idle_ball.empty()) {
			timer_set(AC_TASK_DISPLAY_ID, \
					  AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE, \
					  AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE_INTERAL, \
					  TIMER_PERIODIC);
		}

		if (v_idle_ball.size() < MAX_BALL_DISPLAY) {
			v_idle_ball.push_back(new_ball);
		}
		else {
			BUZZER_PlayTones(tones_3beep);
		}
	}
		break;

	case AC_DISPLAY_BUTON_DOWN_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_DOWN_RELEASED\n");
		if (v_idle_ball.size()) {
			ball::total--;
			v_idle_ball.pop_back();
		}

		if (v_idle_ball.empty()) {
			timer_remove_attr(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE_BALL_MOVING_UPDATE);
		}
	}
		break;

	default:
		break;
	}
}

void ui_state_display_off(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		view_render_display_on();
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;
	default:
		break;
	}
}

/*-------------- [[[ FW UPDATING SCREEN]]] ------------*/
void view_scr_fw_updating() {
	view_render.setTextSize(1);
	view_render.setTextColor(WHITE);
	view_render.setCursor(30, 30);
	view_render.print("Updating ...");
}

void scr_fw_updating_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_DISPLAY_SHOW_FW_UPDATE_ERR: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_FW_UPDATE_ERR\n");
		SCREEN_TRAN(scr_startup_handle, &scr_startup);
		view_render_display_off();
		SCREEN_NONE_UPDATE_MASK();
	}
		break;

	default:
		break;
	}
}

/*-------------- [[[ ACC STATUS SCREEN]]] ------------*/
class line_segment {
public:
	int x0, x1;
	int distance() {
		return (x1 - x0);
	}
};

vector<vector<line_segment>> v_v_backup_chart(2);
vector<int> v_last_st_counter(2);

void view_scr_info() {
	/* link base kit */
	QRCode qrcode;
	uint8_t qrcodeData[qrcode_getBufferSize(8)];
	qrcode_initText(&qrcode, qrcodeData, 8, 0, "https://epcb.vn/products/ak-embedded-base-kit-lap-trinh-nhung-vi-dieu-khien-mcu");

	for (uint8_t y = 0; y < qrcode.size; y++) {
		for (uint8_t x = 0; x < qrcode.size; x++) {
			view_render.drawPixel(x+40, y+2, qrcode_getModule(&qrcode, x, y) ? 1 : 0);
		}
	}

	view_render.setTextSize(1);
	view_render.setCursor(6, 56);
	view_render.print("AK Embedded Base Kit");
}

#define AC_DISPLAY_TIMEOUT_PROTECT_SCR_INFO_INTERVAL	60000	/* 60s */

void scr_info_handle(ak_msg_t* msg) {
	switch (msg->sig) {
	case SCREEN_ENTRY: {
		APP_DBG_SIG("SCREEN_ENTRY\n");
		timer_set(AC_TASK_DISPLAY_ID, AC_DISPLAY_SHOW_IDLE, AC_DISPLAY_LOGO_INTERVAL, TIMER_ONE_SHOT);
	}
		break;

	case AC_DISPLAY_SHOW_IDLE: {
		APP_DBG_SIG("AC_DISPLAY_SHOW_IDLE\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}

	case AC_DISPLAY_BUTON_MODE_RELEASED: {
		APP_DBG_SIG("AC_DISPLAY_BUTON_MODE_RELEASED\n");
		SCREEN_TRAN(scr_idle_handle, &scr_idle);
	}
		break;

	default:
		break;
	}
}
