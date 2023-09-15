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
#include "math.h"
//#include "record.h"


float encoder_R0,encoder_L0;

float E_distanceL,E_distanceR;
float E_speedL,E_speedR;

float E_lpf_distanceL,E_lpf_distanceR;
float E_lpf_speedL,E_lpf_speedR;

float G_hpf_distanceL,G_hpf_distanceR;
float G_hpf_speedL,G_hpf_speedR;


float fusion_distanceL,fusion_distanceR;
float fusion_speedL,fusion_speedR;
float straight_alpha;

float theta_comp_gain;//角度伝達誤差の補償
//float angle_L_database[ANGLE_MEAN_SIZE];
//float angle_R_database[ANGLE_MEAN_SIZE];

//float E_speedR0,E_speedL0;
//float E_accelerationR,E_accelerationL;

void reset_distance(void) {

	E_distanceL = 0;
	E_distanceR = 0;
	E_lpf_distanceL = 0;
	E_lpf_distanceR = 0;
	G_hpf_distanceL = 0;
	G_hpf_distanceR = 0;
	fusion_distanceL=0;
	fusion_distanceR=0;
	straight_alpha=0.85;
	theta_comp_gain=1;

}

void reset_speed(void) {

	G_hpf_speedL=0;
	G_hpf_speedR=0;
	E_lpf_speedL=0;
	E_lpf_speedR=0;
	fusion_speedL=0;
	fusion_speedR=0;
	straight_alpha=0.85;

}

void interupt_calEncoder(void) {
	float angle_R,angle_L;
	float angle_R_mean,angle_L_mean;
	angle_R=encoder_R-encoder_R0;
	if(angle_R>180){angle_R=angle_R-360;}
	if(angle_R<-180){angle_R=angle_R+360;}
	angle_L=-(encoder_L-encoder_L0);
	if(angle_L>180){angle_L=angle_L-360;}
	if(angle_L<-180){angle_L=angle_L+360;}

//	for (int j = ANGLE_MEAN_SIZE-1; j >= 1; j--) {
//		angle_L_database[j] = angle_L_database[j - 1];
//		angle_R_database[j] = angle_R_database[j - 1];
//	}
//	angle_L_database[0] = angle_L;
//	angle_R_database[0] = angle_R;
//	angle_L_mean=0;
//	angle_R_mean=0;
//	for (int j = ANGLE_MEAN_SIZE-1; j >= 0; j--) {
//		angle_L_mean += angle_L_database[j];
//		angle_R_mean += angle_R_database[j];
//	}
//	angle_L_mean /=ANGLE_MEAN_SIZE;
//	angle_R_mean /=ANGLE_MEAN_SIZE;

	//E_speedR0 = E_speedR;
	//E_speedL0 = E_speedL;
	//one_countL = pl_count_encoderL();
	//one_countR = pl_count_encoderR();
	E_speedL = (angle_L) * pi / 180 * TIRE_DIAMETER_L /2 * 1000  / INTERRUPT_TIME*THETA_COMP_L0
			/(THETA_COMP_L0 + theta_comp_gain*(THETA_COMP_L1*sin(encoder_L*pi/180)+THETA_COMP_L2*cos(encoder_L*pi/180)

	+THETA_COMP_L3*sin(2*encoder_L*pi/180)+THETA_COMP_L4*cos(2*encoder_L*pi/180)));
	E_speedR = (angle_R) * pi / 180 * TIRE_DIAMETER_R /2 * 1000 / INTERRUPT_TIME*THETA_COMP_R0
			/ (THETA_COMP_R0 + theta_comp_gain*(THETA_COMP_R1*sin(encoder_R*pi/180)+THETA_COMP_R2*cos(encoder_R*pi/180)
							  +THETA_COMP_R3*sin(2*encoder_R*pi/180)+THETA_COMP_R4*cos(2*encoder_R*pi/180)));
	E_distanceL += E_speedL * INTERRUPT_TIME;
	E_distanceR += E_speedR * INTERRUPT_TIME;

	encoder_L0=encoder_L;
	encoder_R0=encoder_R;

}


void interupt_calFusion(void) {


	E_lpf_speedL = straight_alpha * E_lpf_speedL + (1 - straight_alpha) * E_speedL;
	E_lpf_speedR = straight_alpha * E_lpf_speedR + (1 - straight_alpha) * E_speedR;
	E_lpf_distanceL += E_lpf_speedL * INTERRUPT_TIME;
	E_lpf_distanceR += E_lpf_speedR * INTERRUPT_TIME;


	//G_hpf_speedL = straight_alpha * (G_hpf_speedL + INTERRUPT_TIME * gf_accel);
	//G_hpf_speedR = straight_alpha * (G_hpf_speedL + INTERRUPT_TIME * gf_accel);
	//G_hpf_distanceL += G_hpf_speedL * INTERRUPT_TIME;
	//G_hpf_distanceR += G_hpf_speedR * INTERRUPT_TIME;


	fusion_speedL = straight_alpha * (fusion_speedL + INTERRUPT_TIME * gf_accel) + (1 - straight_alpha) * E_speedL;
	fusion_speedR = straight_alpha * (fusion_speedL + INTERRUPT_TIME * gf_accel) + (1 - straight_alpha) * E_speedR;
	fusion_distanceL += fusion_speedL * INTERRUPT_TIME;
	fusion_distanceR += fusion_speedR * INTERRUPT_TIME;

}
