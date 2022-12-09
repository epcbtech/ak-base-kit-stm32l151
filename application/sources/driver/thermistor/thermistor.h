#ifndef _THERMISTOR_H
#define _THEMISTOR_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#elif defined (STM32L_PLATFORM)
#include "sys_io.h"
#else
#include <WProgram.h>
#endif

/* command out this define to disable debug */
//#define THERMISTOR_DEBUG_EN

#define DEFAULT_NUM_SAMPLES             10
#define DEFAULT_BCOEF                   3950
#define DEFAULT_NOMINAL_RES             10000
#define DEFAULT_NOMINAL_RES             10000

class THERMISTOR
{
public:
    /**
     * Nominal resistance
     */
    uint16_t nominalResistance;

    /**
     * Serial resistance
     */
    uint16_t serialResistance;

    /**
     * Analog Pin
     */
    uint8_t analogPin;

    /**
     * Beta coefficient of the thermistor
     */
    uint16_t bCoefficient;

    /**
     * THERMISTOR
     *
     * Class constructor
     *
     * @param nomRes Nominal resistance at 25 degrees Celsius
     * @param bCoef beta coefficient of the thermistor
     * @param serialRes Value of the serial resistor
     */
    THERMISTOR(uint8_t adcPin, uint16_t nomRes, uint16_t bCoef, uint16_t serialRes);

    /**
     * begin
     *
     * init adc for thermistor
     *
     * @return none
     */
    void begin();

    /**
     * read
     *
     * Read temperature from thermistor
     *
     * @return temperature in 0.01 ºC
     */
    int read();
	int read_kalman();
	int read_f();
};

#endif
