#include "fsm.h"
#include "port.h"
#include "message.h"
#include "timer.h"

#include "sys_ctrl.h"
#include "sys_io.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_if.h"
#include "app_dbg.h"

#include "task_list.h"
#include "task_list_if.h"
#include "task_dbg.h"

void task_dbg(ak_msg_t* msg) {
	switch (msg->sig) {
#if 1
	case AC_DBG_TEST_1: {
		APP_DBG_SIG("AC_DBG_TEST_1\n");
		uint8_t test_buf[64];
		for (int i = 0; i < 64; i++) {
			test_buf[i] = 0xAA;
		}

		ak_msg_t* s_msg = get_common_msg();
		set_if_des_type(s_msg, IF_TYPE_UART_GW);
		set_if_src_type(s_msg, IF_TYPE_UART_AC);
		set_if_des_task_id(s_msg, GW_TASK_DEBUG_ID);
		set_if_sig(s_msg, GW_DEBUG_2);
		set_if_data_common_msg(s_msg, test_buf, 64);

		set_msg_sig(s_msg, AC_UART_IF_COMMON_MSG_OUT);
		task_post(AC_TASK_UART_IF_ID, s_msg);
	}
		break;

	case AC_DBG_TEST_2: {
		APP_DBG_SIG("AC_DBG_TEST_2\n");
		uint8_t test_buf[256];
		for (int i = 0; i < 256; i++) {
			test_buf[i] = 0xAA;
		}

		ak_msg_t* s_msg = get_dynamic_msg();
		set_if_des_type(s_msg, IF_TYPE_UART_GW);
		set_if_src_type(s_msg, IF_TYPE_UART_AC);
		set_if_des_task_id(s_msg, GW_TASK_DEBUG_ID);
		set_if_sig(s_msg, GW_DEBUG_6);
		set_if_data_dynamic_msg(s_msg, test_buf, 256);

		set_msg_sig(s_msg, AC_UART_IF_DYNAMIC_MSG_OUT);
		task_post(AC_TASK_UART_IF_ID, s_msg);
	}
		break;

	case AC_DBG_TEST_3: {
		APP_DBG_SIG("AC_DBG_TEST_3\n");
		uint32_t data_len = get_data_len_dynamic_msg(msg);
		APP_DBG("data_len: %d\n", data_len);

		uint8_t* rev_data = (uint8_t*)malloc(data_len);
		memcpy(rev_data, get_data_dynamic_msg(msg), data_len);
		APP_DBG("rev_data:");
		for (uint32_t i = 0; i < data_len; i++) {
			APP_DBG(" %02X", *(rev_data + i));
		}
		APP_DBG("\n");
		free(rev_data);

		task_post_pure_msg(AC_TASK_DISPLAY_ID, AC_DISPLAY_BUTON_MODE_RELEASED);
	}
		break;

	case AC_DBG_TEST_4: {
		APP_DBG_SIG("AC_DBG_TEST_43\n");
		timer_set(AC_TASK_DBG_ID, AC_DBG_TEST_5, 10, TIMER_ONE_SHOT);
	}
		break;

	case AC_DBG_TEST_5: {
		APP_DBG_SIG("AC_DBG_TEST_5\n");
		ak_msg_t* s_msg = get_dynamic_msg();
		uint8_t* send_data = (uint8_t*)ak_malloc(254);
		for (uint8_t i = 0; i < 254; i++) {
			*(send_data + i) = i;
		}
		set_data_dynamic_msg(s_msg, send_data, 254);
		set_msg_sig(s_msg, AC_DBG_TEST_6);
		task_post(AC_TASK_DBG_ID, s_msg);
		ak_free(send_data);
	}
		break;

	case AC_DBG_TEST_6: {
		APP_DBG_SIG("AC_DBG_TEST_6: %d\n", get_data_len_dynamic_msg(msg));
	}
		break;

	case AC_DBG_TEST_7: {
		APP_DBG_SIG("AC_DBG_TEST_7\n");
		sys_ctrl_delay_ms(500);
		timer_set(AC_TASK_DBG_ID, AC_DBG_TEST_7, 1000, TIMER_ONE_SHOT);
	}
		break;

	case AC_DBG_TEST_8: {
		APP_DBG_SIG("AC_DBG_TEST_8\n");
		sys_ctrl_delay_ms(100);
		timer_set(AC_TASK_DBG_ID, AC_DBG_TEST_8, 2000, TIMER_ONE_SHOT);
	}
		break;

	case AC_DBG_TEST_9: {
		APP_DBG_SIG("AC_DBG_TEST_9\n");
		sys_ctrl_delay_ms(231);
		timer_set(AC_TASK_DBG_ID, AC_DBG_TEST_9, 750, TIMER_ONE_SHOT);
	}
		break;

	case AC_DBG_TEST_10: {
		APP_DBG_SIG("AC_DBG_TEST_10\n");
		uint8_t test_buf[256];
		for (int i = 0; i < 256; i++) {
			test_buf[i] = 0xAA;
		}

		ak_msg_t* s_msg = get_dynamic_msg();
		set_if_des_type(s_msg, IF_TYPE_UART_GW);
		set_if_src_type(s_msg, IF_TYPE_UART_AC);
		set_if_des_task_id(s_msg, GW_TASK_DEBUG_ID);
		set_if_sig(s_msg, GW_DEBUG_1);
		set_if_data_dynamic_msg(s_msg, test_buf, 256);

		set_msg_sig(s_msg, AC_UART_IF_DYNAMIC_MSG_OUT);
		task_post(AC_TASK_UART_IF_ID, s_msg);
	}
		break;
#endif
	default:
		break;
	}
}
