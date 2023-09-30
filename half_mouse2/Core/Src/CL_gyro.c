/*
 * CL_gyro.c
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */


#include "CL_gyro.h"
#include "PL_gyro.h"
#include "PL_timer.h"


float angle,angle_speed;

float anglex,angle_speedx,angle_speedx_set;

float gf_speed,gf_distance,gf_accel;

float omegaX_offset;
float omegaZ_offset;
float accelY_offset;

float angle_speed_ave[10];


void reset_gyro(void) {
	int s = 0;
	angle = 0;
	omegaZ_offset=0;

	for (s = 1; s <= 1000; s++) {
		//ICM20602_DataUpdate();
		omegaZ_offset += gyro.omega_z;
		omegaX_offset += gyro.omega_x;
		accelY_offset += gyro.accel_y;
		wait_ms_NoReset(1);
	}
	omegaZ_offset = omegaZ_offset / 1000;
	omegaX_offset = omegaX_offset / 1000;
	accelY_offset = accelY_offset / 1000;
	//オフセットする文
	//printf("%f,%f\n",gyro.omega_z,omegaZ_offset);

	angle = 0;
	anglex = 0;
	gf_speed = 0;
	gf_distance = 0;
	for (s = 0; s < 10; s++) {
		angle_speed_ave[s] = 0;
	}
}

void interrupt_calGyro(void) {
	int j = 9;
	//angle_speed0 = angle_speed;

	for (j = 9; j >= 1; j--) {
		angle_speed_ave[j] = angle_speed_ave[j - 1];
	}
	angle_speed_ave[0] = (gyro.omega_z - omegaZ_offset)*GYRO_COEFFICIENT;//*0.9525321206299 ;//* 90 / 96*3690/3600*(3600-17)/3600;

	/*angle_speed = ((angle_speed_ave[0] + angle_speed_ave[1] + angle_speed_ave[2]
			+ angle_speed_ave[3] + angle_speed_ave[4] + angle_speed_ave[5]
			+ angle_speed_ave[6] + angle_speed_ave[7] + angle_speed_ave[8]
			+ angle_speed_ave[9]) / 10);*/
	angle_speed = angle_speed_ave[0];
	//angle_speed=(gyro.omega_z-omegaZ_offset)*90/94;//deg/sec
	angle_speedx=gyro.omega_x;
	angle_speedx_set=(gyro.omega_x - omegaX_offset);
	angle += INTERRUPT_TIME * angle_speed; //deg
	anglex += INTERRUPT_TIME * (gyro.omega_x - omegaX_offset); //deg
	//angle_acceleration = (angle_speed - angle_speed0) * 1000; //deg/sec^2
//+0.12*0.02*angle_speed*angle_speed
	gf_accel = (gyro.accel_y - accelY_offset)*ACCEL_COEFFICIENT*1000*GRAVITATION;
	gf_speed += gf_accel * INTERRUPT_TIME;
	gf_distance += gf_speed * INTERRUPT_TIME;




}
