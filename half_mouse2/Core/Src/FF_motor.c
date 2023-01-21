/*
 * FF_motor.c
 *
 *  Created on: 2023/01/21
 *      Author: sf199
 */

#include "FF_motor.h"
#include "CL_encoder.h"

void feedforward_const_accel(float *feedforward_straight,
		float straight_velocity, float straight_acceleration,
		float *feedforward_turning, float turning_velocity,
		float turning_acceleration) {

	if (straight_velocity >= 0) {
		*feedforward_straight = (((Im * ng * straight_acceleration / 1000
				/ TIRE_DIAMETER) + Tw) * Rm / kt)
				+ (straight_velocity / 1000 * ng * kb / TIRE_DIAMETER);
	} else {
		*feedforward_straight = (((Im * ng * straight_acceleration / 1000
				/ TIRE_DIAMETER) - Tw) * Rm / kt)
				+ (straight_velocity / 1000 * ng * kb / TIRE_DIAMETER);
	}
	if (turning_velocity >= 0) {
		*feedforward_turning = (((ImT * ng * turning_acceleration / 1000
				/ TIRE_DIAMETER) + Tw) * Rm / kt)
				+ (turning_velocity / 1000 * ng * kb / TIRE_DIAMETER)
				+*feedforward_straight*SS;
	} else {
		*feedforward_turning = (((ImT * ng * turning_acceleration / 1000
				/ TIRE_DIAMETER) - Tw) * Rm / kt)
				+ (turning_velocity / 1000 * ng * kb / TIRE_DIAMETER)
				+*feedforward_straight*SS;
	}

}
