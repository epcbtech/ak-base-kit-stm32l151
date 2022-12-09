/**
 ******************************************************************************
 * @Author: GaoKong
 * @Date:   05/09/2016
 * @Update:
 * @AnhHH: Add io function for sth11 sensor.
 ******************************************************************************
**/
#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"
#include "system_stm32l1xx.h"
#include "core_cm3.h"
#include "core_cmFunc.h"

#include "../driver/rtc/rtc.h"
#include "../driver/eeprom/eeprom.h"

/*
 * define pin for arduino pinMode/digitalWrite/digitalRead
 * NOTE: define value MUST be deferrent
 */

#define SHT1X_CLK_PIN					(0x01)
#define SHT1X_DATA_PIN					(0x02)

#define SSD1306_CLK_PIN					(0x03)
#define SSD1306_DATA_PIN				(0x04)

#define DS1302_CLK_PIN					(0x05)
#define DS1302_DATA_PIN					(0x06)
#define DS1302_CE_PIN					(0x07)

/******************************************************************************
 *Pin map button
*******************************************************************************/
#define BUTTON_MODE_IO_PIN				(GPIO_Pin_3)
#define BUTTON_MODE_IO_PORT				(GPIOB)
#define BUTTON_MODE_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

#define BUTTON_UP_IO_PIN				(GPIO_Pin_4)
#define BUTTON_UP_IO_PORT				(GPIOB)
#define BUTTON_UP_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

#define BUTTON_DOWN_IO_PIN				(GPIO_Pin_13)
#define BUTTON_DOWN_IO_PORT				(GPIOC)
#define BUTTON_DOWN_IO_CLOCK			(RCC_AHBPeriph_GPIOC)

/*****************************************************************************
 *Pin map led life
******************************************************************************/
#define LED_LIFE_IO_PIN					(GPIO_Pin_11)
#define LED_LIFE_IO_PORT				(GPIOB)
#define LED_LIFE_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map nRF24l01
******************************************************************************/
#define NRF_CE_IO_PIN					(GPIO_Pin_8)
#define NRF_CE_IO_PORT					(GPIOA)
#define NRF_CE_IO_CLOCK					(RCC_AHBPeriph_GPIOA)


#define NRF_CSN_IO_PIN					(GPIO_Pin_9)
#define NRF_CSN_IO_PORT					(GPIOB)
#define NRF_CSN_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

#define NRF_IRQ_IO_PIN					(GPIO_Pin_1)
#define NRF_IRQ_IO_PORT					(GPIOB)
#define NRF_IRQ_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map Flash W2508
******************************************************************************/
#define FLASH_CE_IO_PIN					(GPIO_Pin_14)
#define FLASH_CE_IO_PORT				(GPIOB)
#define FLASH_CE_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/*****************************************************************************
 *Pin map IR
******************************************************************************/
#define IR_RX_IO_PIN					(GPIO_Pin_15)
#define IR_RX_IO_PORT					(GPIOA)
#define IR_RX_IO_CLOCK					(RCC_AHBPeriph_GPIOA)

#define IR_TX_IO_PIN					(GPIO_Pin_10)
#define IR_TX_IO_PORT					(GPIOB)
#define IR_TX_IO_CLOCK					(RCC_AHBPeriph_GPIOB)

#define IR_DIR1_IO_PIN					(GPIO_Pin_15)
#define IR_DIR1_IO_PORT					(GPIOB)
#define IR_DIR1_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

#define IR_DIR2_IO_PIN					(GPIO_Pin_11)
#define IR_DIR2_IO_PORT					(GPIOA)
#define IR_DIR2_IO_CLOCK				(RCC_AHBPeriph_GPIOA)

/*****************************************************************************
 *Pin map DS1302
******************************************************************************/
#define DS1302_CE_IO_PIN				(GPIO_Pin_7)
#define DS1302_CE_IO_PORT				(GPIOB)
#define DS1302_CE_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

#define DS1302_DATA_IO_PIN				(GPIO_Pin_6)
#define DS1302_DATA_IO_PORT				(GPIOB)
#define DS1302_DATA_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

#define DS1302_CLK_IO_PIN				(GPIO_Pin_8)
#define DS1302_CLK_IO_PORT				(GPIOB)
#define DS1302_CLK_IO_CLOCK				(RCC_AHBPeriph_GPIOB)

/****************************************************************************
 *Pin map HS1101
*****************************************************************************/
#define HS1101_OUT_PIN					(GPIO_Pin_0)
#define HS1101_OUT_PORT					(GPIOB)
#define HS1101_OUT_CLOCK				(RCC_AHBPeriph_GPIOB)

#define HS1101_IN_PIN					(GPIO_Pin_5)
#define HS1101_IN_PORT					(GPIOB)
#define HS1101_IN_CLOCK					(RCC_AHBPeriph_GPIOB)

/****************************************************************************
 *Pin map CT sensor
*****************************************************************************/
#define CT1_ADC_PIN						(ADC_Channel_0)
#define CT2_ADC_PIN						(ADC_Channel_2)
#define CT3_ADC_PIN						(ADC_Channel_3)
#define CT4_ADC_PIN						(ADC_Channel_4)

#define CT_ADC_PORT						(GPIOA)
#define CT_ADC_CLOCK					(RCC_APB2Periph_ADC1)
#define CT_ADC_IO_CLOCK					(RCC_AHBPeriph_GPIOA)

/****************************************************************************
 *Pin map CT sensor
*****************************************************************************/
#define THER_ADC_PIN					(GPIO_Pin_1)
#define THER_ADC_PORT					(GPIOA)
#define THER_ADC_IO_CLOCK				(RCC_AHBPeriph_GPIOA)

/****************************************************************************
 *Pin map ssd1306
*****************************************************************************/
#define SSD1306_CLK_IO_PIN				(GPIO_Pin_13)
#define SSD1306_CLK_IO_PORT				(GPIOB)
#define SSD1306_CLK_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

#define SSD1306_DATA_IO_PIN				(GPIO_Pin_12)
#define SSD1306_DATA_IO_PORT			(GPIOB)
#define SSD1306_DATA_IO_CLOCK			(RCC_AHBPeriph_GPIOB)

/******************************************************************************
* button function
*******************************************************************************/
extern void io_button_mode_init();
extern void io_button_up_init();
extern void io_button_down_init();

extern uint8_t io_button_mode_read();
extern uint8_t io_button_up_read();
extern uint8_t io_button_down_read();

/******************************************************************************
* led status function
*******************************************************************************/
extern void led_life_init();
extern void led_life_on();
extern void led_life_off();

/******************************************************************************
* flash IO function
*******************************************************************************/
extern void flash_io_ctrl_init();
extern void flash_cs_low();
extern void flash_cs_high();
extern uint8_t flash_transfer(uint8_t);

/******************************************************************************
* nfr24l01 IO function
*******************************************************************************/
extern void nrf24l01_io_ctrl_init();
extern void nrf24l01_ce_low();
extern void nrf24l01_ce_high();
extern void nrf24l01_csn_low();
extern void nrf24l01_csn_high();

/******************************************************************************
* ir IO function
*******************************************************************************/
extern void timer_50us_init();
extern void timer_50us_enable();
extern void timer_50us_disable();

extern void ir_rev_io_init();
extern void ir_rev_io_irq_disable();
extern void ir_rev_io_irq_enable();

extern void ir_carrier_freq_init();
extern void ir_carrier_freq_on();
extern void ir_carrier_freq_off();
extern void ir_dir_io_config();
extern void ir_select_direction(uint8_t ir_number);	/* 0 -> 3 */

/******************************************************************************
* shtx IO function
*******************************************************************************/
extern void sht1x_clk_input_mode();
extern void sht1x_clk_output_mode();
extern void sht1x_clk_digital_write_low();
extern void sht1x_clk_digital_write_high();

extern void sht1x_data_input_mode();
extern void sht1x_data_output_mode();
extern void sht1x_data_digital_write_low();
extern void sht1x_data_digital_write_high();
extern int  sht1x_data_digital_read();

/******************************************************************************
* ds1302 IO function
*******************************************************************************/
extern void ds1302_ce_input_mode();
extern void ds1302_ce_output_mode();
extern void ds1302_ce_digital_write_low();
extern void ds1302_ce_digital_write_high();

extern void ds1302_clk_input_mode();
extern void ds1302_clk_output_mode();
extern void ds1302_clk_digital_write_low();
extern void ds1302_clk_digital_write_high();

extern void ds1302_data_input_mode();
extern void ds1302_data_output_mode();
extern void ds1302_data_digital_write_low();
extern void ds1302_data_digital_write_high();

extern uint8_t  ds1302_data_digital_read();

/******************************************************************************
* config DAC, COMP, PWM for read hs1101 function
*******************************************************************************/
extern void io_cfg_dac_hs1101();
extern void io_cfg_comp_hs1101();
extern void io_cfg_timer3_hs1101();
extern void io_cfg_timer4_hs1101();
extern void io_hs1101_read_enable();
extern void io_hs1101_read_disable();
extern void io_reset_timer4_capture();
extern void io_start_timer4_capture();
extern uint32_t io_timer4_get_capture();

/******************************************************************************
* adc function
* + themistor sensor
*
* Note: MUST be enable internal clock for adc module.
*******************************************************************************/
/* configure adc peripheral */
extern void io_cfg_adc1(void);

/* adc configure for CT sensor */
extern void adc_ct_io_cfg();
extern uint16_t adc_ct_io_read(uint8_t);

/* adc configure for thermistor sensor */
extern void adc_thermistor_io_cfg();
extern uint16_t adc_thermistor_io_read(uint8_t);

/******************************************************************************
* ssd1306 oled IO function
*******************************************************************************/
extern void ssd1306_clk_input_mode();
extern void ssd1306_clk_output_mode();
extern void ssd1306_clk_digital_write_low();
extern void ssd1306_clk_digital_write_high();

extern void ssd1306_data_input_mode();
extern void ssd1306_data_output_mode();
extern void ssd1306_data_digital_write_low();
extern void ssd1306_data_digital_write_high();
extern int  ssd1306_data_digital_read();

/******************************************************************************
* eeprom function
*******************************************************************************/
#define EEPROM_BASE_ADDRESS         (0x08080000)
#define EEPROM_MAX_SIZE             (0x1000)

extern uint8_t  io_eeprom_read(uint32_t, uint8_t*, uint32_t);
extern uint8_t  io_eeprom_write(uint32_t, uint8_t*, uint32_t);
extern uint8_t  io_eeprom_erase(uint32_t, uint32_t);

/******************************************************************************
* internal flash function
*******************************************************************************/
extern void internal_flash_unlock();
extern void internal_flash_lock();
extern void internal_flash_erase_pages_cal(uint32_t address, uint32_t len);
extern uint8_t internal_flash_write_cal(uint32_t address, uint8_t* data, uint32_t len);

#ifdef __cplusplus
}
#endif

#endif //__IO_CFG_H__
