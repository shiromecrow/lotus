/*
 * cal_acceleration.c
 *
 *  Created on: 2023/01/16
 *      Author: sf199
 */

#include "cal_acceleration.h"

#include "PL_timer.h"



float mollifier_timer;

volatile char g_acc_flag;
volatile char g_MotorEnd_flag;


void cal_table(TRAPEZOID input,TARGET *target){
float time_over;
if (input.displacement>=0){
	switch (g_acc_flag) {
	case 0:
		//速度FBなし
		break;
	case 1:
		//加速(減速)
			if (target->velocity >= input.count_velocity){
				target->velocity = input.count_velocity;
				target->acceleration = 0;
				g_acc_flag=2;
			}
			else if((input.displacement <= (2*target->velocity*target->velocity
					-input.start_velocity*input.start_velocity
					-input.end_velocity*input.end_velocity)
					/2/input.acceleration)){
				time_over=((2*target->velocity*target->velocity
						-input.start_velocity*input.start_velocity
						-input.end_velocity*input.end_velocity)
						/2/input.acceleration-input.displacement)/target->velocity;
				target->displacement -= 1/2*INTERRUPT_TIME*input.acceleration*(2*time_over);
				target->velocity -= input.acceleration*(2*time_over);

				target->acceleration = -input.acceleration;
				g_acc_flag=3;
			}
		break;
	case 2:
		//定常
		if (input.displacement-target->displacement <=
				(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2/input.acceleration) {
			time_over=(target->displacement+(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2
						/input.acceleration-input.displacement)/target->velocity;
			target->displacement -= 1/2*INTERRUPT_TIME*input.acceleration*time_over;
			target->velocity -= input.acceleration*(time_over);

			target->acceleration = -input.acceleration;
			g_acc_flag=3;
		}
		break;
	case 3:
		//減速(加速)
		if (target->velocity <= input.end_velocity){
			target->velocity = input.end_velocity;
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 4:
		//終了(0でもいいかも)
		break;
	case 5:
		//加速のみ
		if (target->displacement >= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 6:
		//減速のみ
		if (target->displacement >= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	}
}else{
	switch (g_acc_flag) {
	case 0:
		//速度FBなし
		break;
	case 1:
		//加速(減速)
			if (target->velocity <= input.count_velocity){
				target->velocity = input.count_velocity;
				target->acceleration = 0;
				g_acc_flag=2;
			}

			else if((-input.displacement <= (2*target->velocity*target->velocity
					-input.start_velocity*input.start_velocity
					-input.end_velocity*input.end_velocity)
					/2/input.acceleration)){
				time_over=(-(2*target->velocity*target->velocity
						-input.start_velocity*input.start_velocity
						-input.end_velocity*input.end_velocity)
						/2/input.acceleration-input.displacement)/target->velocity;
				target->displacement += 1/2*INTERRUPT_TIME*input.acceleration*(2*time_over);
				target->velocity += input.acceleration*(2*time_over);

				target->acceleration = input.acceleration;
				g_acc_flag=3;
			}
		break;
	case 2:
		//定常
		if (-input.displacement+target->displacement <=
				(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2/input.acceleration) {
			time_over=(target->displacement-(input.count_velocity*input.count_velocity
						-input.end_velocity*input.end_velocity)/2
						/input.acceleration-input.displacement)/target->velocity;
			target->displacement += 1/2*INTERRUPT_TIME*input.acceleration*time_over;
			target->velocity += input.acceleration*(time_over);

			target->acceleration = input.acceleration;
			g_acc_flag=3;
		}
		break;
	case 3:
		//減速(加速)
		if (target->velocity >= input.end_velocity){
			target->velocity = input.end_velocity;
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 4:
		//終了(0でもいいかも)
		g_MotorEnd_flag=1;
		break;
	case 5:
		//加速のみ
		if (target->displacement <= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	case 6:
		//減速のみ
		if (target->displacement <= input.displacement){
			target->acceleration = 0;
			g_acc_flag=4;
		}
		break;
	}

}

}





void cal_mollifier_table(MOLLIFIER input,TARGET *target){

float mollifier_T;
float old_velocity;
float time_delay=15;
float time_delay2=-15;
	mollifier_timer+=INTERRUPT_TIME;
		mollifier_T=2*fabs(input.displacement)/MOLLIFIER_INTEGRAL*exp(-1)/input.max_turning_velocity;
		if (mollifier_timer>-mollifier_T/2 && mollifier_timer<mollifier_T/2){
			old_velocity=target->velocity;
			target->velocity = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-mollifier_timer*mollifier_timer));
			//if(mollifier_timer<0){
			if(mollifier_timer<-mollifier_T/2/1.316+time_delay*INTERRUPT_TIME){
				target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(-mollifier_T/2/1.316)/(mollifier_T*mollifier_T/4-(-mollifier_T/2/1.316)*(-mollifier_T/2/1.316))/(mollifier_T*mollifier_T/4-(-mollifier_T/2/1.316)*(-mollifier_T/2/1.316)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(-mollifier_T/2/1.316)*(-mollifier_T/2/1.316)));
			}else if(mollifier_timer<0){
				target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(mollifier_timer-INTERRUPT_TIME*time_delay)/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay))/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)));
			}else if(mollifier_timer<mollifier_T/2/1.316+time_delay2*INTERRUPT_TIME){
				//target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(mollifier_timer-INTERRUPT_TIME*time_delay2)/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay2)*(mollifier_timer-INTERRUPT_TIME*time_delay2))/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay2)*(mollifier_timer-INTERRUPT_TIME*time_delay2)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay2)*(mollifier_timer-INTERRUPT_TIME*time_delay2)));
				target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(mollifier_timer-INTERRUPT_TIME*time_delay)/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay))/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)));
			}else{
				time_delay=0;
				target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(mollifier_timer-INTERRUPT_TIME*time_delay)/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay))/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(mollifier_timer-INTERRUPT_TIME*time_delay)*(mollifier_timer-INTERRUPT_TIME*time_delay)));
//				target->acceleration = (2/mollifier_T)*input.displacement/MOLLIFIER_INTEGRAL*(-mollifier_T*mollifier_T/2*(mollifier_T/2/1.316)/(mollifier_T*mollifier_T/4-(mollifier_T/2/1.316)*(mollifier_T/2/1.316))/(mollifier_T*mollifier_T/4-(mollifier_T/2/1.316)*(mollifier_T/2/1.316)))*exp(-mollifier_T*mollifier_T/4/(mollifier_T*mollifier_T/4-(mollifier_T/2/1.316)*(mollifier_T/2/1.316)));;
				//target->acceleration = 0;
			}
//			if(mollifier_timer>-mollifier_T/2*0.35 && mollifier_timer<mollifier_T/2*0.45){
//							target->acceleration = 0.7*target->acceleration;
//			}
//			if(mollifier_timer>mollifier_T/2*0.6){
//							target->acceleration = 0.4*target->acceleration;
//			}
//			if(mollifier_timer>mollifier_T/2*0.9){
//							target->acceleration = -0.6*target->acceleration;
//			}
		}else{
			old_velocity=target->velocity;
			target->velocity=0;
			target->acceleration = target->velocity-old_velocity;
			g_acc_flag=4;
		}

}

