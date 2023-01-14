/*
 * Control_motor.c
 *
 *  Created on: Jan 14, 2023
 *      Author: sf199
 */


#include "Control_motor.h"
#include "CL_gyro.h"
#include "CL_sensor.h"
#include "CL_encoder.h"
#include "PL_motor.h"
#include "PL_LED.h"
#include "PL_timer.h"
//#include "fail_safe.h"

#include "math.h"

//#include "PID_wall.h"

//#include "maze_wall.h"
//#include "maze_strategy.h"


/*


void Control_mode_Init(void){

	modeacc = 0;
	g_MotorEnd_flag=0;
	mollifier_timer=0;
	noGoalPillarMode=0;

}




void interupt_DriveMotor(void){
	int duty_L=0, duty_R=0;
	float V_L=0, V_R=0;
	float PID_all_L,PID_all_R,PID_s,PID_t;
	float PID_w=0;
	float feedforward_straight=0,feedforward_turning=0;

//	interrupt_WallCut();

	if (modeacc == 0) {
		g_acc_flag=4;
//		g_WallControl_mode=0;
//		g_wallCut_mode=0;
		//g_acc_flag=0;
	}
	if (modeacc == 1) {
		g_MotorTimCount++;
		straight.displacement += straight.velocity*INTERRUPT_TIME + straight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		straight.velocity += straight.acceleration*INTERRUPT_TIME;
		turning.displacement += turning.velocity*INTERRUPT_TIME + turning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		turning.velocity += turning.acceleration*INTERRUPT_TIME;
//		if(straight.velocity>=4500 && g_acc_flag==1){
//			straight.acceleration=13000;
//			if(straight.acceleration<=0){
//				straight.acceleration=0;
//			}
//		}
		cal_table(Trapezoid_straight,&straight);
		motor_PID(&PID_all_L,&PID_all_R,&PID_s,&PID_t,&PID_w);
		feedforward_const_accel(&feedforward_straight,&feedforward_turning);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean+feedforward_straight-feedforward_turning;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean+feedforward_straight+feedforward_turning;
		if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight>g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}else if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight<-g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);
	}
	if (modeacc == 2 || modeacc == 4) {//旋回とスラローム
		g_MotorTimCount++;
		straight.displacement += straight.velocity*INTERRUPT_TIME + straight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		straight.velocity += straight.acceleration*INTERRUPT_TIME;
		turning.displacement += turning.velocity*INTERRUPT_TIME + turning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		turning.velocity += turning.acceleration*INTERRUPT_TIME;
		cal_table(Trapezoid_turning,&turning);
		motor_PID(&PID_all_L,&PID_all_R,&PID_s,&PID_t,&PID_w);
		feedforward_const_accel(&feedforward_straight,&feedforward_turning);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean+feedforward_straight-feedforward_turning;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean+feedforward_straight+feedforward_turning;
		if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight>g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}else if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight<-g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);
	}
	if (modeacc == 3) {//宴会芸
		g_MotorTimCount++;
		straight.displacement += straight.velocity*INTERRUPT_TIME + straight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		straight.velocity += straight.acceleration*INTERRUPT_TIME;
		turning.displacement += turning.velocity*INTERRUPT_TIME + turning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		turning.velocity += turning.acceleration*INTERRUPT_TIME;
		motor_PID(&PID_all_L,&PID_all_R,&PID_s,&PID_t,&PID_w);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean;
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);
	}if (modeacc == 5) {//前壁制御
		calFrontWallConrol(&PID_frontwall_l,&PID_frontwall_r);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean;
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);
	}if (modeacc == 6) {//ネイピア加速
		straight.displacement += straight.velocity*INTERRUPT_TIME + straight.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		straight.velocity += straight.acceleration*INTERRUPT_TIME;
		turning.displacement += turning.velocity*INTERRUPT_TIME;// + turning.acceleration*INTERRUPT_TIME*INTERRUPT_TIME/2;
		cal_mollifier_table(Mollifier_turning,&turning);//角速度と角加速度はここで決定
		motor_PID(&PID_all_L,&PID_all_R,&PID_s,&PID_t,&PID_w);
		if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight>g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}else if(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight<-g_V_battery_mean*MAX_DUTY_RATIO_ST){
			V_L+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
			V_R+=-g_V_battery_mean*MAX_DUTY_RATIO_ST-(PID_s/ MAXMOTOR * g_V_battery_mean+feedforward_straight);
		}
		feedforward_const_accel(&feedforward_straight,&feedforward_turning);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean+feedforward_straight-feedforward_turning;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean+feedforward_straight+feedforward_turning;
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);

	}if (modeacc == 100) {
		straight.velocity = 0;
		turning.velocity=0;
		motor_PID(&PID_all_L,&PID_all_R,&PID_s,&PID_t,&PID_w);
		V_L = PID_all_L / MAXMOTOR * g_V_battery_mean;
		V_R = PID_all_R / MAXMOTOR * g_V_battery_mean;
		get_duty(V_L, V_R,&duty_L,&duty_R);
		pl_DriveMotor_duty(duty_L,duty_R);
	}
		g_V_L=(float)(V_L);//V_L;
		g_V_R=(float)(V_R);//V_R;



}


*/
