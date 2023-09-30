/*
 * CL_encoder.h
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */

#ifndef INC_CL_ENCODER_H_
#define INC_CL_ENCODER_H_

#include "stm32g4xx_hal.h"

#define TIRE_DIAMETER_L 0.0118088*1.1126*396/399.73*400/398.99*737/720*718231/719839.1*708/720//m  dayo*****************************************
#define TIRE_DIAMETER_R 0.0118088*1.1126*396/399.73*400/402.66*737/720*708/720//m  dayo*****************************************
#define TIRE_DIAMETER (TIRE_DIAMETER_L+TIRE_DIAMETER_R)/2
//*real_dis/goal_dis    * Lのほうに　*sum_R/sum_L
#define pi 3.1415926535


#define	THETA_COMP_R0	1794.515693
#define	THETA_COMP_R1	-9.648232689
#define	THETA_COMP_R2	124.239828
#define	THETA_COMP_R3	5.81E+01
#define	THETA_COMP_R4	350.9497737
#define	THETA_COMP_L0	1697.543763
#define	THETA_COMP_L1	3.578765229
#define	THETA_COMP_L2	-105.2054722
#define	THETA_COMP_L3	-272.9594973
#define	THETA_COMP_L4	98.91691051

#define	ANGLE_MEAN_SIZE 200




extern float E_distanceR,E_distanceL;
extern float E_speedR,E_speedL;

extern float E_lpf_distanceL,E_lpf_distanceR;
extern float E_lpf_speedL,E_lpf_speedR;

extern float G_hpf_distanceL,G_hpf_distanceR;
extern float G_hpf_speedL,G_hpf_speedR;


extern float fusion_distanceL,fusion_distanceR;
extern float fusion_speedL,fusion_speedR;
extern float straight_alpha;

extern float theta_comp_gain;//角度伝達誤差の補償
//extern float E_speedR0,E_speedL0;
//extern float E_accelerationR,E_accelerationL;

void reset_distance();
void reset_speed();
void encoder_distance();
void interupt_calEncoder();
void interupt_calFusion();

#endif /* INC_CL_ENCODER_H_ */
