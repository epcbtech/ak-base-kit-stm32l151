#include "fsm.h"
#include "port.h"
#include "timer.h"
#include "message.h"

#include "sys_ctrl.h"
#include "sys_dbg.h"

#include "app.h"
#include "app_dbg.h"

#include "sys_irq.h"
#include "sys_io.h"

#include "task_list.h"
#include "task_zigbee.h"

#include "xprintf.h"
#include "ring_buffer.h"

#include "hex.h"
#include "Arduino.h"
#include "HardwareSerial.h"

using namespace std;

//https://github.com/athombv/homey/issues/2165
//https://github.com/Frans-Willem/AqaraHub/blob/master/documentation/devices/lumi.sensor_ht.md

#define DBG_ZB_FRAME_EN //Enable debug raw frame.
#define DBG_ZB_EN //Enable print for zigbee debug.

#if defined(DBG_ZB_EN)
#define ZB_DBG(fmt, ...)       xprintf(fmt, ##__VA_ARGS__)
#else
#define ZB_DBG(fmt, ...)
#endif

zb_znp zigbee_network(&Serial3);

/* Biến xử lý điều khiển switch */
uint8_t control_switch_cmd_seq = 0;
uint16_t control_switch_address = 0;

int zb_znp::zigbee_message_handler(zigbee_msg_t& zigbee_msg) {
	/* zigbee start debug message */
#if defined (DBG_ZB_FRAME_EN)
	ZB_DBG("[ZB msg] len: %d cmd0: %x cmd1: %x \n", zigbee_msg.len, zigbee_msg.cmd0, zigbee_msg.cmd1);
	ZB_DBG(" data: ");
	for (int i = 0; i < zigbee_msg.len; i++) {
		ZB_DBG("%x ", (uint8_t)zigbee_msg.data[i]);
	}
	ZB_DBG("\n");
#endif
	/* zigbee stop debug message */

	uint16_t zigbee_cmd = BUILD_UINT16(zigbee_msg.cmd1, zigbee_msg.cmd0);

	switch(zigbee_cmd) {
	case ZDO_MGMT_LEAVE_REQ: {
		ZB_DBG("ZDO_MGMT_LEAVE_REQ\n");
	}
		break;

	case ZB_RECEIVE_DATA_INDICATION: {
		ZB_DBG("ZB_RECEIVE_DATA_INDICATION\n");
	}
		break;

	case UTIL_GET_DEVICE_INFO_RESPONSE: {
		uint8_t zb_mac_string[17];
		bytestoHexChars((uint8_t*)&zigbee_msg.data[1], 8, (uint8_t*) &zb_mac_string[0]);
		zb_mac_string[16] = '\0';

		ZB_DBG("COORDINATOR IEEEAddr: %s\n", zb_mac_string);
	}
		break;

	case ZDO_ACTIVE_EP_RES: {
		APP_PRINT("ZDO_ACTIVE_EP_REQ_STATUS: %d\n", zigbee_msg.data[2]);
	}
		break;

	case ZDO_ACTIVE_EP_RSP: {
		APP_PRINT("ZDO_ACTIVE_EP_RSP\n");
		APP_PRINT("Status        : %d\n", zigbee_msg.data[2]);
		uint16_t DEVICE_ADDRESS = BUILD_UINT16(zigbee_msg.data[0], zigbee_msg.data[1]);
		APP_PRINT("DEVICE ADDRESS: %04X\n", DEVICE_ADDRESS);
		uint8_t ActiveEPCount = zigbee_msg.data[5];
		APP_PRINT("ActiveEPCount : %d\n", ActiveEPCount);

		for (uint8_t i = 6; i < (ActiveEPCount + 6); i++) {
			APP_PRINT("ActiveEPList  : %d\n", zigbee_msg.data[i]);
		}

	}
		break;

	case AF_INCOMING_MSG: {

		#if defined (TASK_BUZZER_EN)
			BUZZER_PlayTones(tones_startup);
		#endif

		ZB_DBG("ZB_RECEIVE_DATA_INDICATION\n");
		afIncomingMSGPacket_t* st_af_incoming_msg = (afIncomingMSGPacket_t*)zigbee_msg.data;

		zclProcMsgStatus_t zclProcMsgStatus = zcl_ProcessMessageMSG(st_af_incoming_msg);
		switch (zclProcMsgStatus) {
		case ZCL_PROC_SUCCESS: 					{ ZB_DBG("Message was processed\n"); } break;
		case ZCL_PROC_INVALID:					{ ZB_DBG("Format or parameter was wrong\n"); } break;
		case ZCL_PROC_EP_NOT_FOUND:				{ ZB_DBG("Endpoint descriptor not found\n"); } break;
		case ZCL_PROC_NOT_OPERATIONAL: 			{ ZB_DBG("Can't respond to this command\n"); } break;
		case ZCL_PROC_INTERPAN_FOUNDATION_CMD:	{ ZB_DBG("INTER-PAN and Foundation Command (not allowed)\n"); } break;
		case ZCL_PROC_NOT_SECURE: 				{ ZB_DBG("Security was required but the message is not secure\n"); } break;
		case ZCL_PROC_MANUFACTURER_SPECIFIC: 	{ ZB_DBG("Manufacturer Specific command - not handled\n"); } break;
		case ZCL_PROC_MANUFACTURER_SPECIFIC_DR:	{ ZB_DBG("Manufacturer Specific command - not handled, but default response sent\n"); } break;
		case ZCL_PROC_NOT_HANDLED: 				{ ZB_DBG("No default response was sent and the message was not handled\n"); } break;
		case ZCL_PROC_NOT_HANDLED_DR: 			{ ZB_DBG("default response was sent and the message was not handled\n"); } break;
		default: { ZB_DBG("Status: %d\n", zclProcMsgStatus); } break;
		}

#if defined (DBG_ZB_FRAME_EN)
		ZB_DBG("AF_INCOMING_MSG:\n");
		ZB_DBG("\tgroup_id: %04x \n", st_af_incoming_msg->group_id);
		ZB_DBG("\tcluster_id: %04x\n", st_af_incoming_msg->cluster_id);
		ZB_DBG("\tsrc_addr: %04x\n", st_af_incoming_msg->src_addr);
		ZB_DBG("\tsrc_endpoint: %x\n", st_af_incoming_msg->src_endpoint);
		ZB_DBG("\tdst_endpoint: %x\n", st_af_incoming_msg->dst_endpoint);
		ZB_DBG("\twas_broadcast: %x\n", st_af_incoming_msg->was_broadcast);
		ZB_DBG("\tlink_quality: %x\n", st_af_incoming_msg->link_quality);
		ZB_DBG("\tsecurity_use: %x\n", st_af_incoming_msg->security_use);
		ZB_DBG("\ttime_stamp: %08x\n", st_af_incoming_msg->time_stamp);
		ZB_DBG("\ttrans_seq_num: %x\n", st_af_incoming_msg->trans_seq_num);
		ZB_DBG("\tlen: %d\n", st_af_incoming_msg->len);
		ZB_DBG("\tdata: ");
		for (int i = 0 ; i < st_af_incoming_msg->len ; i++) {
			ZB_DBG("%02x ", st_af_incoming_msg->payload[i]);
		}
		ZB_DBG("\n");
#endif
	}
		break;

	case ZDO_MGMT_LEAVE_RSP: {
		ZB_DBG("ZDO_MGMT_LEAVE_RSP\n");
	}
		break;

	case ZDO_MGMT_PERMIT_JOIN_RSP: {
		ZB_DBG("ZDO_MGMT_PERMIT_JOIN_RSP\n");
	}
		break;

	case ZDO_TC_DEV_IND: {
		ZB_DBG("ZDO_TC_DEV_IND\n");
	}
		break;

	case ZDO_END_DEVICE_ANNCE_IND: {
#if defined (DBG_ZB_FRAME_EN)
		ZDO_DeviceAnnce_t* ZDO_DeviceAnnce = (ZDO_DeviceAnnce_t*)zigbee_msg.data;
		ZB_DBG("\tSrcAddr: %04x \n", ZDO_DeviceAnnce->SrcAddr);
		ZB_DBG("\tnwkAddr: %04x \n", ZDO_DeviceAnnce->nwkAddr);
		ZB_DBG("\textAddr: ");
		for (int i = 0 ; i < Z_EXTADDR_LEN ; i++) {
			xprintf("%02x ", ZDO_DeviceAnnce->extAddr[i]);
		}

		xprintf("\n");

		ZB_DBG("\n");
		/***
			 * Specifies the MAC capabilities of the device.
			 * Bit: 0 – Alternate PAN Coordinator
			 * 1 – Device type: 1- ZigBee Router; 0 – End Device
			 * 2 – Power Source: 1 Main powered
			 * 3 – Receiver on when idle
			 * 4 – Reserved
			 * 5 – Reserved
			 * 6 – Security capability
			 * 7 – Reserved
			 */
		ZB_DBG("\tcapabilities: %d\n", ZDO_DeviceAnnce->capabilities);
#endif
	}
		break;

	default: {
		ZB_DBG("zigbee_cmd: 0x%02X\n", zigbee_cmd);
	}
		break;
	}

	return 0;
}

void task_zigbee(ak_msg_t* msg) {
	switch (msg->sig) {
	case AC_ZIGBEE_INIT: {
		APP_DBG_SIG("AC_ZIGBEE_INIT\n");
	}
		break;

	case AC_ZIGBEE_FORCE_START_COODINATOR: {
		APP_DBG_SIG("AC_ZIGBEE_FORCE_START_COODINATOR\n");
		if (zigbee_network.start_coordinator(1) == 0) {
			ZB_DBG("force start_coordinator successfully\n");

			/* Get IEEE Address of Coordinator */
			#if defined(TASK_ZIGBEE_EN)
					timer_set(AC_TASK_ZIGBEE_ID, AC_ZIGBEE_UTIL_GET_DEVICE_INFO_REQ, 3000, TIMER_ONE_SHOT);
			#endif

		}
		else {
			ZB_DBG("force start_coordinator error\n");
		}
	}
		break;

	case AC_ZIGBEE_START_COODINATOR: {
		APP_DBG_SIG("AC_ZIGBEE_START_COODINATOR\n");
		if (zigbee_network.start_coordinator(0) == 0) {
			ZB_DBG("start_coordinator successfully\n");
		}
		else {
			ZB_DBG("start_coordinator error\n");
		}
	}
		break;

	case AC_ZIGBEE_PERMIT_JOINING_REQ: {
		APP_DBG_SIG("AC_ZIGBEE_PERMIT_JOINING_REQ\n");
		zigbee_network.set_permit_joining_req(ALL_ROUTER_AND_COORDINATOR, 60, 1);
	}
		break;

	case AC_ZIGBEE_ZCL_CONTROL_DEVICE_REQ: {
		APP_DBG_SIG("AC_ZIGBEE_ZCL_CONTROL_DEVICE_REQ\n");
		uint8_t st_buffer[3] = { /* Frame control */ 0x01,
								 /* Transaction Sequence Number */0x00,  /* control_switch_cmd_seq++ */
								 /* Value Control */ 0x02}; /* Value Control [ 0x00:OFF , 0x01:ON , 0x02:TOOGLE ] */
		st_buffer[1] = control_switch_cmd_seq++;

		af_data_request_t st_af_data_request;
		st_af_data_request.cluster_id    = ZCL_CLUSTER_ID_SMART_RELAY_ON_OFF;
		st_af_data_request.dst_address   = 0x444f;
		st_af_data_request.dst_endpoint  = 11;
		st_af_data_request.src_endpoint  = 0x01;
		st_af_data_request.trans_id      = 0x00;
		st_af_data_request.options       = 0x10;
		st_af_data_request.radius        = 0x0F;
		st_af_data_request.len           = 3;
		st_af_data_request.data          = st_buffer;

		zigbee_network.send_af_data_req(st_af_data_request);
	}
		break;

	case AC_ZIGBEE_UTIL_GET_DEVICE_INFO_REQ: {
		zigbee_network.util_get_device_info();
	}
		break;

	case AC_ZIGBEE_ZDO_GET_ACTIVE_EP_REQ: {
		APP_PRINT("AC_ZIGBEE_ZDO_GET_ACTIVE_EP_REQ\n");
		zigbee_network.zdo_active_ep_req(0x444f);
	}
		break;

	case AC_ZIGBEE_ZCL_CMD_HANDLER: {
		APP_DBG_SIG("AC_ZIGBEE_ZCL_CMD_HANDLER\n");

		zclOutgoingMsg_t* pOutgoingMsg = (zclOutgoingMsg_t*)(*(uint32_t*)get_data_common_msg(msg));

		ZB_DBG("[zclMsg] short_addr = 0x%04x\n", pOutgoingMsg->short_addr);
		ZB_DBG("[zclMsg] cluster_id = 0x%04x\n", pOutgoingMsg->cluster_id);
		ZB_DBG("[zclMsg] group_id = 0x%04x\n", pOutgoingMsg->group_id);
		ZB_DBG("[zclMsg] cmd = 0x%02x\n", pOutgoingMsg->cmd);
		ZB_DBG("[zclMsg] attrID = 0x%04x\n", pOutgoingMsg->attrID);
		ZB_DBG("[zclMsg] dataType = 0x%02x\n", pOutgoingMsg->dataType);
		ZB_DBG("[zclMsg] dataLen = %d\n", pOutgoingMsg->dataLen);
		ZB_DBG("[zclMsg] data: ");
		for (int i = 0 ; i < pOutgoingMsg->dataLen ; i++) {
			ZB_DBG("%02x ", pOutgoingMsg->data[i]);
		}
		ZB_DBG("\n");

		// Handle data message incoming.
		switch (pOutgoingMsg->cluster_id) {
		case ZCL_CLUSTER_ID_MS_RELATIVE_HUMIDITY: {
			ZB_DBG("ZCL_CLUSTER_ID_MS_RELATIVE_HUMIDITY\n");
			uint16_t retHum = (uint16_t)(pOutgoingMsg->data[pOutgoingMsg->dataLen] + pOutgoingMsg->data[pOutgoingMsg->dataLen - 1] * 256);
			(void)retHum;
			// Ví dụ: retHum = 6789, thì giá trị trả về là 67,89 %
			ZB_DBG("HUMIDITY: %0.2f\n", (float)(retHum / 100));
		}
			break;

		case ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT: {
			ZB_DBG("ZCL_CLUSTER_ID_MS_TEMPERATURE_MEASUREMENT\n");
			uint16_t retTemp = (uint16_t)(pOutgoingMsg->data[pOutgoingMsg->dataLen] + pOutgoingMsg->data[pOutgoingMsg->dataLen - 1] * 256);
			(void)retTemp;
			// Ví dụ: retTemp = 2723, thì giá trị trả về là 27,23 *C
			ZB_DBG("TEMPERATURE: %0.2f\n", (float)(retTemp / 100));
		}
			break;

		case ZCL_CLUSTER_ID_GEN_BASIC: {
			ZB_DBG("ZCL_CLUSTER_ID_GEN_BASIC\n");
			switch (pOutgoingMsg->attrID) {
			case ATTRID_XIAOMI_SENS_STATUS_REPORT: {
				if (pOutgoingMsg->dataLen == sizeof(xiaomi_sens_status_report_t) &&
						pOutgoingMsg->data[1] == 1) {

					uint8_t battery_level = 0;
					(void)battery_level;
					xiaomi_sens_status_report_t xiaomi_sens_status_report;
					memcpy(&xiaomi_sens_status_report, pOutgoingMsg->data, sizeof(xiaomi_sens_status_report_t));
					ZB_DBG("<SENS> BATTERY VOLTAGE: %d\n", xiaomi_sens_status_report.battery_value);

					//https://devzone.nordicsemi.com/f/nordic-q-a/28101/how-to-calculate-battery-voltage-into-percentage-for-aa-2-batteries-without-fluctuations
					if (xiaomi_sens_status_report.battery_value >= 3000) {
						xiaomi_sens_status_report.battery_value  = 100;
					}
					else if (xiaomi_sens_status_report.battery_value > 2900) {
						battery_level = 100 - ((3000 - xiaomi_sens_status_report.battery_value ) * 60) / 100;
					}
					else if (xiaomi_sens_status_report.battery_value > 2740) {
						battery_level = 60 - ((2900 - xiaomi_sens_status_report.battery_value) * 40) / 150;
					}
					else {
						battery_level = 0;
					}

					ZB_DBG("<SENS> BATTERY PERCENT: %d\n", battery_level);
					ZB_DBG("<SENS> TEMPERATURE: %d\n", xiaomi_sens_status_report.temperatemure_value / 100);
					ZB_DBG("<SENS> HUMIDITY: %d\n", xiaomi_sens_status_report.humidity_value / 100);
				}
			}
				break;

			default:
				break;
			}
		}
			break;

		default:
			break;
		}

		// free message.
		if (pOutgoingMsg) {
			ak_free(pOutgoingMsg);
		}

		if (pOutgoingMsg->data) {
			ak_free(pOutgoingMsg->data);
		}
	}
		break;

	default:
		break;
	}
}

