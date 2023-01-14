/*
 * CL_encoder.h
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */

#ifndef INC_CL_ENCODER_H_
#define INC_CL_ENCODER_H_

#include "stm32g4xx_hal.h"

#define TIRE_DIAMETER 0.0118088*562/540*535/540*535/540*520/540//m  dayo*****************************************
#define pi 3.1415926535

extern float E_distanceR,E_distanceL;
extern float E_speedR,E_speedL;

extern float E_lpf_distanceL,E_lpf_distanceR;
extern float E_lpf_speedL,E_lpf_speedR;

extern float G_hpf_distanceL,G_hpf_distanceR;
extern float G_hpf_speedL,G_hpf_speedR;


extern float fusion_distanceL,fusion_distanceR;
extern float fusion_speedL,fusion_speedR;
extern float straight_alpha;
//extern float E_speedR0,E_speedL0;
//extern float E_accelerationR,E_accelerationL;

void reset_distance();
void reset_speed();
void encoder_distance();
void interupt_calEncoder();
void interupt_calFusion();

#endif /* INC_CL_ENCODER_H_ */
