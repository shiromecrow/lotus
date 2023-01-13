/*
 * CL_gyro.h
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */

#ifndef INC_CL_GYRO_H_
#define INC_CL_GYRO_H_

#define GYRO_COEFFICIENT 0.949359*3520/3600*732/720*3555/3600
#define ACCEL_COEFFICIENT 1.230*1.1



extern float angle,angle_speed;

extern float anglex,angle_speedx;

extern float gf_speed,gf_distance,gf_accel;




void reset_gyro(void);

void interrupt_calGyro(void);

#endif /* INC_CL_GYRO_H_ */
