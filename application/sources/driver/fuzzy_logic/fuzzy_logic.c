#include "fuzzy_logic.h"

#include "sys_dbg.h"

#include "app_dbg.h"

fuzzy_logic_temperature_t temp_fuzzy_logic;

uint8_t temp_fuzzy_logic_set( float cool,float normal , float hot) {
	float d1,d1x,d1y;
	float d2,d2x,d2y;
	float d3,d3x,d3y;
	float d4,d4x,d4y;
	float a1,a2,a3,a4;
	float b1,b2,b3,b4;

	if(cool < 0 || normal < cool || hot < normal || hot > 100){
		return FUZZY_LOGIC_NG;
	}

	d1 =  cool - normal;
	d1x = -FUZZY_LOGIC_PERCENT;
	d1y = (cool * FUZZY_LOGIC_PERCENT);
	a1 = d1x / d1;
	b1 = d1y / d1;

	d2  = (normal - hot);
	d2x = FUZZY_LOGIC_PERCENT;
	d2y = -(hot * FUZZY_LOGIC_PERCENT);
	a2 = d2x / d2;
	b2 = d2y / d2;

	d3 =  (cool - normal);
	d3x = FUZZY_LOGIC_PERCENT;
	d3y = - (normal * FUZZY_LOGIC_PERCENT);
	a3 = d3x / d3;
	b3 = d3y / d3;

	d4 = (normal- hot);
	d4x = -FUZZY_LOGIC_PERCENT;
	d4y = (normal * FUZZY_LOGIC_PERCENT);
	a4 = d4x / d4;
	b4 = d4y / d4;

	temp_fuzzy_logic.cool	= cool;
	temp_fuzzy_logic.normal = normal;
	temp_fuzzy_logic.hot	= hot;

	temp_fuzzy_logic.fuzzy_logic.e_lower.a1		= a1;
	temp_fuzzy_logic.fuzzy_logic.e_lower.b1		= b1;
	temp_fuzzy_logic.fuzzy_logic.e_lower.a2		= a3;
	temp_fuzzy_logic.fuzzy_logic.e_lower.b2		= b3;
	temp_fuzzy_logic.fuzzy_logic.e_higher.a1	= a2;
	temp_fuzzy_logic.fuzzy_logic.e_higher.b1	= b2;
	temp_fuzzy_logic.fuzzy_logic.e_higher.a2	= a4;
	temp_fuzzy_logic.fuzzy_logic.e_higher.b2	= b4;

	return FUZZY_LOGIC_OK;
}

fuzzy_logic_temperature_t* temp_fuzzy_logic_get() {
	return &temp_fuzzy_logic;
}

void temp_fuzzy_logic_update(fuzzy_logic_temperature_t* fuzzy_logic) {
	memcpy(&temp_fuzzy_logic, fuzzy_logic, sizeof(fuzzy_logic_temperature_t));
}

uint8_t temp_fuzzy_logic_cal(uint8_t* level, uint8_t* percent, float temp) {
	float y1_normal,y2_normal,y_cool,y_hot;

	if (level == (uint8_t*)0 || percent == (uint8_t*)0 ) {
		return FUZZY_LOGIC_NG;
	}

	if (temp <= temp_fuzzy_logic.cool) {
		*percent = FUZZY_LOGIC_PERCENT;
		*level = FUZZY_LOGIC_COOL;
	}

	if (temp >= temp_fuzzy_logic.hot) {
		*percent = FUZZY_LOGIC_PERCENT;
		*level = FUZZY_LOGIC_HOT;
	}

	if (temp >temp_fuzzy_logic.cool && temp < temp_fuzzy_logic.normal ) {
		y1_normal = temp_fuzzy_logic.fuzzy_logic.e_lower.a1 * temp + temp_fuzzy_logic.fuzzy_logic.e_lower.b1;
		y_cool = temp_fuzzy_logic.fuzzy_logic.e_lower.a2 * temp + temp_fuzzy_logic.fuzzy_logic.e_lower.b2;

		if (y1_normal >= y_cool) {
			*percent =(uint8_t)y1_normal;
			*level = FUZZY_LOGIC_NORMAL;
		}
		else {
			*percent = (uint8_t)y_cool;
			*level = FUZZY_LOGIC_COOL;
		}
	}

	if (temp >=temp_fuzzy_logic.normal && temp < temp_fuzzy_logic.hot ) {
		y2_normal = temp_fuzzy_logic.fuzzy_logic.e_higher.a1 * temp + temp_fuzzy_logic.fuzzy_logic.e_higher.b1;
		y_hot = temp_fuzzy_logic.fuzzy_logic.e_higher.a2 * temp + temp_fuzzy_logic.fuzzy_logic.e_higher.b2;

		if (y2_normal >= y_hot) {
			*percent =(uint8_t)y2_normal;
			*level = FUZZY_LOGIC_NORMAL;
		}
		else {
			*percent = (uint8_t)y_hot;
			*level = FUZZY_LOGIC_HOT;
		}
	}

	return FUZZY_LOGIC_OK;
}
