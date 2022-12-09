#include "kalman.h"
#include "sys_dbg.h"
#include "app_dbg.h"

uint16_t kalman_filter(uint16_t signal_in) {
	static uint8_t counter = 0;
	static float A,H,Q,R,X,P;
	static float value_return=0;

	uint16_t ret = 0;
	float XP,PP;
	float K;
	float temp_float;

	if (counter < 1) {
		counter++;
	}

	if (counter == 1) {
		A = 1;
		H = 1;			//1
		Q = 0.32;		//earlier 0.92,0.02
		R = 0.2514285714;
		X = 250;
		counter = 2;

		XP = A*X;
		PP = A*P*A + Q;

		K = PP*H;
		K /=(H*H*PP)+R;

		temp_float = (float)(signal_in-H*XP);
		value_return = XP + K*temp_float;

		temp_float = H*PP;
		P = PP-K*temp_float;
		ret = (uint16_t)value_return;
	}
	else {
		XP = A*value_return;
		PP = A*P*A + Q;

		K = PP*H;
		K /=(H*H*PP)+R;

		temp_float = (float)(signal_in-H*XP);
		value_return = XP + K*temp_float;

		temp_float = (float)H*PP;
		P = PP-K*temp_float;
		ret = (uint16_t)value_return;
	}

	return ret;
}
