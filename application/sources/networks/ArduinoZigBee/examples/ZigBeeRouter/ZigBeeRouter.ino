#include <zb_znp.h>
#include <zb_zcl.h>
#include <SoftwareSerial.h>

#define DBG_ZB_FRAME

SoftwareSerial znp_serial(2, 3);
zb_znp zigbee_network(&znp_serial);

int zb_znp::zigbee_message_handler(zigbee_msg_t& zigbee_msg) {
	/* zigbee start debug message */
	Serial.print("[ZB msg] len: ");
	Serial.print(zigbee_msg.len);
	Serial.print(" cmd0: ");
	Serial.print(zigbee_msg.cmd0, HEX);
	Serial.print(" cmd1: ");
	Serial.print(zigbee_msg.cmd1, HEX);
	Serial.print(" data: ");
	for (int i = 0; i < zigbee_msg.len; i++) {
		Serial.print(zigbee_msg.data[i], HEX);
		Serial.print(" ");
	}
	Serial.println("");
	/* zigbee stop debug message */

	uint16_t zigbee_cmd = BUILD_UINT16(zigbee_msg.cmd1, zigbee_msg.cmd0);

	switch(zigbee_cmd) {
	case ZDO_MGMT_LEAVE_REQ: {
		Serial.println("ZDO_MGMT_LEAVE_REQ");
	}
		break;

	case ZB_RECEIVE_DATA_INDICATION: {
		Serial.println("ZB_RECEIVE_DATA_INDICATION");
	}
		break;

	case ZDO_MGMT_PERMIT_JOIN_RSP: {
		Serial.println("ZDO_MGMT_PERMIT_JOIN_RSP");
		ZdoMgmtPermitJoinRspInd_t* ZdoMgmtPermitJoinRspInd = (ZdoMgmtPermitJoinRspInd_t*)zigbee_msg.data;
		Serial.print("\tsrcaddr: ");
		Serial.println(ZdoMgmtPermitJoinRspInd->srcaddr);
		Serial.print("\tstatus: ");
		Serial.println(ZdoMgmtPermitJoinRspInd->status);
	}
		break;

	case ZDO_TC_DEV_IND: {
		Serial.println("ZDO_TC_DEV_IND");
	}
		break;

	case AF_DATA_REQUEST_IND: {
		Serial.println("AF_DATA_REQUEST_IND");
		uint8_t* status = (uint8_t*)zigbee_msg.data;
		Serial.print("\tstatus: ");
		Serial.println(*status);
	}
		break;

	case AF_DATA_CONFIRM: {
		Serial.println("AF_DATA_CONFIRM");
		afDataConfirm_t* afDataConfirm = (afDataConfirm_t*)zigbee_msg.data;
		Serial.print("\tstatus: ");
		Serial.println(afDataConfirm->status);
		Serial.print("\tendpoint: ");
		Serial.println(afDataConfirm->endpoint);
		Serial.print("\ttransID: ");
		Serial.println(afDataConfirm->transID);
	}
		break;

	case AF_INCOMING_MSG: {
		afIncomingMSGPacket_t* st_af_incoming_msg = (afIncomingMSGPacket_t*)zigbee_msg.data;
		Serial.println("AF_INCOMING_MSG");

#if defined (DBG_ZB_FRAME)
		Serial.print("group_id: "); Serial.println(st_af_incoming_msg->group_id, HEX);
		Serial.print("cluster_id: "); Serial.println(st_af_incoming_msg->cluster_id, HEX);
		Serial.print("src_addr: "); Serial.println(st_af_incoming_msg->src_addr, HEX);
		Serial.print("src_endpoint: "); Serial.println(st_af_incoming_msg->src_endpoint, HEX);
		Serial.print("dst_endpoint: "); Serial.println(st_af_incoming_msg->dst_endpoint, HEX);
		Serial.print("was_broadcast: "); Serial.println(st_af_incoming_msg->was_broadcast, HEX);
		Serial.print("link_quality: "); Serial.println(st_af_incoming_msg->link_quality, HEX);
		Serial.print("security_use: "); Serial.println(st_af_incoming_msg->security_use, HEX);
		Serial.print("time_stamp: "); Serial.println(st_af_incoming_msg->time_stamp, HEX);
		Serial.print("trans_seq_num: "); Serial.println(st_af_incoming_msg->trans_seq_num, HEX);
		Serial.print("len: "); Serial.println(st_af_incoming_msg->len);
		Serial.print("data: ");
		for (int i = 0 ; i < st_af_incoming_msg->len ; i++) {
			Serial.print(st_af_incoming_msg->payload[i], HEX);
			Serial.print(" ");
		}
		Serial.println("");
#endif
	}
		break;

	case ZDO_MGMT_LEAVE_RSP: {
		Serial.println("ZDO_MGMT_LEAVE_RSP");
	}
		break;
	}
}

void setup() {
	Serial.begin(115200);
	znp_serial.begin(115200);
	znp_serial.setTimeout(100);

	/* Kh???i ?????ng router */
	Serial.println("\nstart_router");
	/* (opt = 0)
	 * to normal start router, and keep configures.
	 * (opt = 1)
	 * to force start router, reset configures to default.
	 * (opt = 2)
	 * to auto start router.
	 */
	if (zigbee_network.start_router(1) == 0) {
		Serial.println("start router successfully");
	}
	else {
		Serial.println("start router error");
	}
}

/* k?? t??? t???m ????? x??? l?? y??u c???u t??? terminal */
char serial_cmd;

void loop() {
	/* h??m update() ph???i ???????c g???i trong v??ng l???p ????? x??? l?? c??c g??i tin nh???n ???????c t??? ZigBee Shield */
	zigbee_network.update();

	/* Ki???m tra / th???c hi???n c??c l???nh t??? terminal */
	if (Serial.available()) {
		serial_cmd = Serial.read();

		switch(serial_cmd) {
			/* G???i request cho router join v??o coordinator */
		case '1': {
			Serial.println("bdb_start_commissioning");
			zigbee_network.bdb_start_commissioning(COMMISSIONING_MODE_STEERING, 1, 1);
		}
			break;

			/* G???i data t??? router ?????n coordinator */
		case '2': {
			Serial.println("send_af_data_req\n");

			uint8_t st_buffer[3] = { 0x01, 0x02, 0x03}; // data mu???n g???i ??i

			af_data_request_t st_af_data_request;
			st_af_data_request.cluster_id    = 0x0000;
			st_af_data_request.dst_address   = 0x0000;
			st_af_data_request.dst_endpoint  = 0X01;
			st_af_data_request.src_endpoint  = 0X01;
			st_af_data_request.trans_id      = 0x00;
			st_af_data_request.options       = 0X10;
			st_af_data_request.radius        = 0x0F;
			st_af_data_request.len           = sizeof(st_buffer);
			st_af_data_request.data          = st_buffer;

			zigbee_network.send_af_data_req(st_af_data_request);
		}
			break;

			/******************************************************************
			 *  V?? d???:
			 * g???i data t??? Router ?????n Gateway (coodinator)
			 * c??c th??ng s??? c???n thi???t cho qu?? tr??nh n??y bao g???m
			 * 2. ????? d??i c???a m???ng data c???n truy???n
			 * 3. data

		case 's': {
			uint8_t st_buffer[10];
			af_data_request_t st_af_data_request;
			st_af_data_request.cluster_id    = 0x0000;
			st_af_data_request.dst_address   = 0x0000; // ?????a ch??? c???a coodinator lu??n l?? 0x0000
			st_af_data_request.dst_endpoint  = 0x01;
			st_af_data_request.src_endpoint  = 0x01;
			st_af_data_request.trans_id      = 0x00;
			st_af_data_request.options       = 0x10;
			st_af_data_request.radius        = 0x0F;
			st_af_data_request.len           = [ ????? d??i data c???n g???i ??i ] v?? d???: sizeof(st_buffer)
			st_af_data_request.data          = [ data ] v?? d???: st_buffer
			zigbee_network.send_af_data_req(st_af_data_request);
		}
			break;
			********************************************************************/

		default:
			break;
		}
	}
}
