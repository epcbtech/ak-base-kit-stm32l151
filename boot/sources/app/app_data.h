#ifndef __APP_DATA_H__
#define __APP_DATA_H__

#include <stdint.h>
#include "app.h"

/******************************************************************************
* Data type of RF24Network
*******************************************************************************/
#define RF24_DATA_COMMON_MSG_TYPE			(1)
#define RF24_DATA_PURE_MSG_TYPE				(2)
#define RF24_DATA_REMOTE_CMD_TYPE			(3)

/******************************************************************************
* Commom data structure for transceiver data
*******************************************************************************/
#define FIRMWARE_PSK		0x1A2B3C4D
#define FIRMWARE_LOK		0x1234ABCD

typedef struct {
	uint8_t is_power_on_reset;
} boot_app_share_data_t;

extern boot_app_share_data_t boot_app_share_data;

#endif //__APP_DATA_H__
