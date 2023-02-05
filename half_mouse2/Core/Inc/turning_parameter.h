/*
 * turning_parameter.h
 *
 *  Created on: 2023/01/31
 *      Author: sf199
 */

#ifndef INC_TURNING_PARAMETER_H_
#define INC_TURNING_PARAMETER_H_

typedef struct {
	float g_speed;
		float f_ofset;
		float e_ofset;
		float t_speed;
		float t_acc;
} parameter;


typedef struct {

float SlalomCentervelocity;
float TurnCentervelocity;

parameter slalom_R;
parameter slalom_L;
parameter turn90_R;
parameter turn90_L;
parameter turn180_R;
parameter turn180_L;
parameter turn45in_R;
parameter turn45in_L;
parameter turn135in_R;
parameter turn135in_L;
parameter turn45out_R;
parameter turn45out_L;
parameter turn135out_R;
parameter turn135out_L;
parameter V90_R;
parameter V90_L;

}parameter_speed;


extern parameter_speed speed300_exploration;
extern parameter_speed speed300_shortest;
extern parameter_speed speed800_shortest;
extern parameter_speed speed800_shortest_mollifier;

float get_center_velocity(parameter_speed,int);

void input_parameter();



#endif /* INC_TURNING_PARAMETER_H_ */
