/*
 * fail_safe.c
 *
 *  Created on: 2023/01/20
 *      Author: sf199
 */


#include "fail_safe.h"
#include "CL_gyro.h"
#include "Control_motor.h"
#include "PID_EncoderGyro.h"
#include"CL_sensor.h"

#include "PL_LED.h"
#include "CL_encoder.h"
#include "PL_motor.h"
#include "PID_wall.h"

#include "record.h"
//#include"maze_strategy.h"
//#include"maze_wall.h"

#include "math.h"

char no_safty;
char error_mode;
char highspeed_mode;
float encoder_PID_error;
float gyro_PID_error;
float gyro_x_error;
float encoder_PID_error_highspeed;
float gyro_PID_error_highspeed;
float gyro_x_error_highspeed;
int error_time_count;

void init_FailSafe(void){
	error_mode=0;
	no_safty=0;
	highspeed_mode = 0;
	error_time_count=0;
	encoder_PID_error=1500;
	gyro_PID_error=800;
	gyro_x_error=1500;

	encoder_PID_error_highspeed=3500;//3000
	gyro_PID_error_highspeed=1900;
	gyro_x_error_highspeed=1900;
}


void interrupt_FailSafe(void){
	float encoder_PID_error_in;
	float gyro_PID_error_in;
	float gyro_x_error_in;

	if (highspeed_mode == 0) {
		encoder_PID_error_in=encoder_PID_error;
		gyro_PID_error_in=gyro_PID_error;
		gyro_x_error_in=gyro_x_error;
	}else{
		encoder_PID_error_in=encoder_PID_error_highspeed;
		gyro_PID_error_in=gyro_PID_error_highspeed;
		gyro_x_error_in=gyro_x_error_highspeed;
	}

	if (modeacc != 0 && modeacc != 3){
		if (no_safty == 0 && error_mode == 0) {
			//ジャイロの誤差が一定以上
					if (fabs(turning.velocity - angle_speed) >= gyro_PID_error_in ) {
						//(gyro.omega_x >= 320 && gyro.omega_y >= 320) ||
						//pl_DriveMotor_stop();
						pl_FunMotor_stop();
						//pl_DriveMotor_standby(OFF);
						pl_yellow_LED_count(1);
						error_mode = 1;
						clear_Ierror();
					}
					if (angle_speedx_set >= gyro_x_error_in) {
						//pl_DriveMotor_stop();
						pl_FunMotor_stop();
						//pl_DriveMotor_standby(OFF);
						pl_yellow_LED_count(2);
						error_mode = 1;
						clear_Ierror();
					}
					if(fabs(straight.velocity - (fusion_speedR+fusion_speedL)/2) >= encoder_PID_error_in && modeacc==1){
						//pl_DriveMotor_stop();
						pl_FunMotor_stop();
						//pl_DriveMotor_standby(OFF);
						pl_yellow_LED_count(4);
						error_mode = 1;
						clear_Ierror();
					}

				}

	}

	if(error_mode==1){
		record_mode=0;
		error_time_count++;
		if(error_time_count<=1000){
			init_WallControl();
			modeacc=100;//エラー用
			//pl_R_DriveMotor_mode(MOTOR_BREAK);
			//pl_L_DriveMotor_mode(MOTOR_BREAK);
		}else{
			pl_DriveMotor_standby(OFF);
			pl_DriveMotor_stop();
			pl_FunMotor_stop();
			modeacc=0;
		}
					NoWallCountL90 = 4294967295;
					NoWallCountR90 = 4294967295;
					NoWallCountL45 = 4294967295;
					NoWallCountR45 = 4294967295;
					NoWallCountL45slant = 4294967295;
					NoWallCountR45slant = 4294967295;
					NoWallDisplacementL90 = 50;
					NoWallDisplacementR90 = 50;
					NoWallDisplacementL45 = 20;
					NoWallDisplacementR45 = 20;
					NoWallDisplacementL45slant = 35;
					NoWallDisplacementR45slant = 35;
					NoWallDisplacementL45slant2 = 35;
					NoWallDisplacementR45slant2 = 35;
					g_acc_flag=4;
					g_wallCut_mode = 0;
					//maze_mode=0;

	}else{
		error_time_count=0;
	}


}
