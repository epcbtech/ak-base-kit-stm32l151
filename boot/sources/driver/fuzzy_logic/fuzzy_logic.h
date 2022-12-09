#ifndef __FUZZY_LOGIC_H__
#define __FUZZY_LOGIC_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

#define FUZZY_LOGIC_OK				(0x00)
#define FUZZY_LOGIC_NG				(0x01)

#define FUZZY_LOGIC_COOL			(0x01)
#define FUZZY_LOGIC_NORMAL			(0x02)
#define FUZZY_LOGIC_HOT				(0x03)
#define FUZZY_LOGIC_PERCENT			(100)

typedef struct {
	float a1, b1;
	float a2, b2;
} equations_t;

typedef struct {
	equations_t e_higher;
	equations_t e_lower;
} fuzzy_logic_equations_t;

typedef struct {
	fuzzy_logic_equations_t fuzzy_logic;
	uint8_t cool;
	uint8_t normal;
	uint8_t hot;
} fuzzy_logic_temperature_t;

extern uint8_t temp_fuzzy_logic_set(float cool, float normal, float hot);
extern fuzzy_logic_temperature_t* temp_fuzzy_logic_get();
extern void temp_fuzzy_logic_update(fuzzy_logic_temperature_t* fuzzy_logic);
extern uint8_t temp_fuzzy_logic_cal(uint8_t* level, uint8_t* percent, float temp);

#ifdef __cplusplus
}
#endif

#endif //__FUZZY_LOGIC_H__
