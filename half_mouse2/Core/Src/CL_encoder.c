/*
 * CL_encoder.c
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */


#include "CL_encoder.h"
#include "PL_encoder.h"
#include "CL_gyro.h"
#include "PL_timer.h"
//#include "record.h"


float encoder_R0,encoder_L0;

float E_distanceL,E_distanceR;
float E_speedL,E_speedR;
float fusion_distanceL,fusion_distanceR;
float fusion_speedL,fusion_speedR;
float straight_alpha;
//float E_speedR0,E_speedL0;
//float E_accelerationR,E_accelerationL;

void reset_distance(void) {

	E_distanceL = 0;
	E_distanceR = 0;
	fusion_distanceL=0;
	fusion_distanceR=0;
	straight_alpha=0.65;

}

void reset_speed(void) {

	fusion_speedL=0;
	fusion_speedR=0;
	straight_alpha=0.65;

}

void interupt_calEncoder(void) {
	float angle_R,angle_L;
	angle_R=encoder_R-encoder_R0;
	if(angle_R>180){angle_R=angle_R-360;}
	if(angle_R<-180){angle_R=angle_R+360;}
	angle_L=-(encoder_L-encoder_L0);
	if(angle_L>180){angle_L=angle_L-360;}
	if(angle_L<-180){angle_L=angle_L+360;}

	//E_speedR0 = E_speedR;
	//E_speedL0 = E_speedL;
	//one_countL = pl_count_encoderL();
	//one_countR = pl_count_encoderR();
	E_speedL = (angle_L) * TIRE_DIAMETER * 1000 * pi / 180 / 39 * 9 * 1000;
	E_speedR = (angle_R) * TIRE_DIAMETER * 1000 * pi / 180 / 39 * 9 * 1000;
	E_distanceL += E_speedL / 1000;
	E_distanceR += E_speedR / 1000;

	encoder_L0=encoder_L;
	encoder_R0=encoder_R;

}


void interupt_calFusion(void) {



	fusion_speedL = straight_alpha * (fusion_speedL + INTERRUPT_TIME * gf_accel) + (1 - straight_alpha) * E_speedL;
	fusion_speedR = straight_alpha * (fusion_speedL + INTERRUPT_TIME * gf_accel) + (1 - straight_alpha) * E_speedR;
	fusion_distanceL += fusion_speedL / 1000;
	fusion_distanceR += fusion_speedR / 1000;

}
