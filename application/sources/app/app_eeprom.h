#ifndef __APP_EEPROM_H__
#define __APP_EEPROM_H__
#include <stdint.h>
#include "app.h"

/**
  *****************************************************************************
  * EEPROM define address.
  *
  *****************************************************************************
  */
#define EEPROM_START_ADDR								(0X0000)
#define EEPROM_END_ADDR									(0X1000)

#define EEPROM_APP_SETTING_ADDR							(0x0000)		/* setting information */

#define EEPROM_APP_NETWORK_CONFIG_ADDR					(0x00F0)		/* network configure */

#define EEPROM_APP_IR_HEADER_BASE_ADDR					(0x0100)		/* IR header */

#define EEPROM_AIR_COND_START_BASE_ADDR					(0x0140)		/* status of air conditions */

#define EEPROM_FATAL_LOG_ADDR							(0x0F00)		/* fatal information */


/**
  *****************************************************************************
  * default setting value.
  *
  *****************************************************************************
  */
#define APP_SETTING_DEFAUL_TOTAL_AIR_COND				(2)
#define APP_SETTING_DEFAUL_TOTAL_AIR_COND_ALTERNATE		(1)
#define APP_SETTING_DEFAUL_TOTAL_AIR_COND_MODE_AUTO		(1) /* 1: AUTO, 2: MANUAL */

#define APP_SETTING_DEFAUL_MILESTONE_TEMP_COOL			(20)
#define APP_SETTING_DEFAUL_MILESTONE_TEMP_NORMAL		(25)
#define APP_SETTING_DEFAUL_MILESTONE_TEMP_HOT			(30)

#define APP_SETTING_DEFAUL_MILESTONE_AIR_COND_ON		(100)

#define APP_SETTING_DEFAUL_ERASE_LOG_MEM_EN				(1)

#define APP_SETTING_DEFAUL_TIME_AIR_COUNTER				(0)
#define APP_SETTING_NUMBER_TIME_AIR_RANGE				(8)

#define APP_SETTING_DEFAUL_TEMP_CALIBRATION				(0)
#define APP_SETTING_DEFAUL_HUM_CALIBRATION				(20)

#define APP_SETTING_DEFAUL_OPTS_TEMP_CALIBRATION		(0)
#define APP_SETTING_DEFAUL_OPTS_HUM_CALIBRATION			(0)

#define APP_SETTING_DEFAUL_NODE_CHANEL					(90)
#define APP_SETTING_DEFAUL_NODE_ADDR					(1)
#define APP_SETTING_DEFAUL_NODE_SERVER_ADDR				(0)


typedef struct {
	uint32_t address;
	uint32_t len;
} ir_cmd_info_t;

typedef struct {
	ir_cmd_info_t on;
	ir_cmd_info_t off;
} app_ir_cmd_info_t;

typedef struct {
	app_ir_cmd_info_t air_cond_ir_cmd[4];
} app_airconds_ir_cmd_info_t;

#endif //__APP_EEPROM_H__
