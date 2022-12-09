#if (ARDUINO >= 100)
#include <Arduino.h>
#elif defined (STM32L_PLATFORM)
#include "Arduino.h"
#include "io_cfg.h"
#else
#include <WProgram.h>
#endif

#include "thermistor.h"
#include "kalman.h"

#if defined(THERMISTOR_DEBUG_EN)
#include "app_dbg.h"
#endif

// Temperature for nominal resistance (almost always 25 C)
#define TEMPERATURENOMINAL 25
// Number of ADC samples
#define NUMSAMPLES         5
// ADC resolution
#define ADC_RESOLUTION          4095
#define VERBOSE_SENSOR_ENABLED  1
/**
 * THERMISTOR
 *
 * Class constructor
 *
 * @param adcPin Analog pin where the thermistor is connected
 * @param nomRes Nominal resistance at 25 degrees Celsius
 * @param bCoef beta coefficient of the thermistor
 * @param serialRes Value of the serial resistor
 */
THERMISTOR::THERMISTOR(uint8_t adcPin, uint16_t nomRes, uint16_t bCoef, uint16_t serialRes)
{
	analogPin = adcPin;
	nominalResistance = nomRes;
	bCoefficient = bCoef;
	serialResistance = serialRes;
}

/**
 * begin
 *
 * init adc for thermistor
 *
 * @return none
 */
void THERMISTOR::begin(void) {
	adc_thermistor_io_cfg();
}

/**
 * read
 *
 * Read temperature from thermistor
 *
 * @return temperature in 0.1 ºC
 */
int THERMISTOR::read(void)
{
	uint8_t i;
	uint16_t sample;
	float average = 0;

	//analogReference(DEFAULT);

	// take N samples in a row, with a slight delay
	for (i=0; i< NUMSAMPLES; i++)
	{
		sample = adc_thermistor_io_read(analogPin);
		average += sample;
		delay(10);
	}
	average /= NUMSAMPLES;
#if defined(THERMISTOR_DEBUG_EN)
	APP_DBG("Average analog reading = :%d\n",(int)average);
#endif

	// convert the value to resistance
	average = ADC_RESOLUTION / average - 1;
	average = serialResistance / average;
#if defined(THERMISTOR_DEBUG_EN)
	APP_DBG("Thermistor resistance : %d\n",(int)average);
#endif

	float steinhart;
	steinhart = (average / nominalResistance);   // (R/Ro)
	steinhart = log(steinhart);                  // ln(R/Ro)
	steinhart /= bCoefficient;                   // 1/B * ln(R/Ro)
	steinhart += (float)1.0 / ((float)TEMPERATURENOMINAL + (float)273.15); // + (1/To)
	steinhart = (float)1.0 / steinhart;                 // Invert
	steinhart -= (float)273.15;                         // convert to C
#if defined(THERMISTOR_DEBUG_EN)
	APP_DBG("Temperature =:%d *C\n",(int)steinhart);
#endif
	return (int)(steinhart * 10);
}

int THERMISTOR::read_kalman() {
#if defined(THERMISTOR_DEBUG_EN)
	uint16_t temp = (uint16_t)read_f();
	int ret = (int)kalman_filter(temp);
	APP_DBG("raw:%d\n", temp);
	APP_DBG("kalman:%d\n", ret);
	return ret;
#else
	return (int)kalman_filter((uint16_t)read_f());
#endif
}

int THERMISTOR::read_f() {
	int temp;

	temp = read();

	if(temp > 500 || temp < 150) {
		temp = 990;
	}
	return temp;
}
