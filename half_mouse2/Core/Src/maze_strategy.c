/*
 * maze_strategy.c
 *
 *  Created on: 2023/06/29
 *      Author: sf199
 */

#include"maze_strategy.h"
#include"Control_motor.h"
#include"define.h"
#include"maze_Turning.h"
#include "PID_EncoderGyro.h"
#include "PID_wall.h"

#include"maze_wall.h"
#include"PL_flash.h"
#include "CL_sensor.h"
#include "PL_motor.h"
#include "PL_LED.h"
#include "PL_timer.h"
#include "fail_safe.h"
#include "math.h"
#include "record.h"




//extern char highspeed_mode;
//extern int safe;
//extern int mode_safty;
//extern char slant_direction;
//extern char slant_count;
//
//unsigned short row_record[15];
//unsigned short column_record[15];
//unsigned short row_record_look[15];
//unsigned short column_record_look[15];
int do_move;//ごみ
unsigned short shift5 = 1;
unsigned short kakuninn;
unsigned short wall_N;
unsigned short wall_S;
unsigned short wall_E;
unsigned short wall_W;
unsigned short wall_f;
unsigned short wall_r;
unsigned short wall_l;
unsigned short look_f;
unsigned short look_l;
unsigned short look_r;
unsigned short fb_control;
unsigned short rl_control;

unsigned char min;
unsigned char min_coordinate;

unsigned char pass_count;

int x_change;
int y_change;

int hosuu = 0;
char first_most = 0;
char kitiku;
int kitiku_distance;
char know_road = 0;
float first_v;
float last_v;


int x;
int y;
int wall_control;
int SENF_maze, SENR_maze, SENL_maze;
int direction;


char maze_mode;
int kitikukan;

int pass[255]; //1f 2r 3l
int gg;


//拡張左手法**************************************************
//
//unsigned short shift = 1;
//
//unsigned short aa;
//unsigned short bb;
//
int t = 0;

//int way = 0;
//int p = 0;
//int s = 0;
//int q = 0;
//char last_slant;
//char slant_break;
//拡張左手法***********************************************



void update_coordinate(int *x,int *y,int direction){
// int direction,int *x_coordinate,int *y_coordinate
//	*direction = *direction % 4;
//	if (*direction <= 0) {
//		*direction = *direction+4;
//	}
	switch (direction) {
	case 1://北
		*y += 1;
		break;
	case 2://東
		*x += 1;
		break;
	case 3://南
		*y -= 1;
		break;
	case 4://西
		*x -= 1;
		break;
	}



}




void AdatiWayReturn(float input_StraightVelocity, float input_TurningVelocity, float input_StraightAcceleration,
		float input_TurningAcceleration, parameter_speed howspeed,int know_mode,uint8_t Dijkstra_mode) {
	unsigned short front_count, right_count, back_count, left_count;
//	float v_e,v_ea;

	maze_mode = 1; //***************************************************************************************
	//Avespeed = 700;
	pl_DriveMotor_standby(ON);
	HAL_Delay(500);
//初期化
	//構造体にする
	int x=0;
	int y=0;
	int direction=1;
	_Bool front_wall;
	_Bool right_wall;
	_Bool left_wall;
	char timer_end_mode=0;
	MOTOR_MODE mode;
	mode.WallControlMode=1;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;


//初期位置のセンサー確認
	front_wall=(g_sensor_mean[SENSOR_FRONT] >= F_PRESENCE);
	right_wall=(g_sensor_mean[SENSOR_RIGHT] >= R_PRESENCE);
	left_wall=(g_sensor_mean[SENSOR_LEFT] >= L_PRESENCE);

	update_wall(x,y,direction,front_wall,right_wall,left_wall);
	//初期位置での迷路展開
	create_StepCountMap_queue();
	HAL_Delay(100);
	straight_table2(90/2+BACK_TO_CENTER,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

	while (1) {

		//straight_table2(90, 300, 300, 500);

		update_coordinate(&x,&y,direction);


		front_wall=(g_sensor_mean[SENSOR_FRONT] >= F_PRESENCE);
		right_wall=(g_sensor_mean[SENSOR_RIGHT] >= R_PRESENCE);
		left_wall=(g_sensor_mean[SENSOR_LEFT] >= L_PRESENCE);

		mode.WallControlMode=1;
		mode.calMazeMode=1;
		mode.WallCutMode=0;
		straight_table2(MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
		update_wall(x,y,direction,front_wall,right_wall,left_wall);
		if(Dijkstra_mode==2){
					route_Dijkstra();
					create_StepCountMap_unknown();
				}else{
					create_StepCountMap_queue();
				}
		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
		if (front_wall) {front_count = MAX_WALKCOUNT;}
		if (right_wall) {right_count = MAX_WALKCOUNT;}
		if (left_wall) {left_count = MAX_WALKCOUNT;}
		decision_kitiku(x,y,direction,front_count,right_count,back_count,left_count);
		mode.WallCutMode=1;
		End_straight(MAZE_OFFSET, mode,right_wall,left_wall);



		if (x == 0 && y == 0) {break;}

		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){


			while (front_wall==0) {
				//直進
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2(180/2-MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

				update_coordinate(&x,&y,direction);

				front_wall=(g_sensor_mean[SENSOR_FRONT] >= F_PRESENCE);
				right_wall=(g_sensor_mean[SENSOR_RIGHT] >= R_PRESENCE);
				left_wall=(g_sensor_mean[SENSOR_LEFT] >= L_PRESENCE);

				mode.WallControlMode=1;
				mode.calMazeMode=1;
				mode.WallCutMode=0;
				straight_table2(MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				update_wall(x,y,direction,front_wall,right_wall,left_wall);
				create_StepCountMap_queue();
				search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
				if (front_wall) {front_count = MAX_WALKCOUNT;}
				if (right_wall) {right_count = MAX_WALKCOUNT;}
				if (left_wall) {left_count = MAX_WALKCOUNT;}
				mode.WallCutMode=1;
				End_straight(MAZE_OFFSET,mode,right_wall,left_wall);


			}
			mode.WallControlMode=0;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			straight_table2(90/2-MAZE_OFFSET, input_StraightVelocity,0,input_StraightVelocity,input_StraightAcceleration, mode);
			pl_R_DriveMotor_mode(MOTOR_BREAK);
			pl_L_DriveMotor_mode(MOTOR_BREAK);
			wait_ms_NoReset(500);
			no_safty = 1;
			turning_table2(180,0,0,input_TurningVelocity,input_TurningAcceleration);
			pl_R_DriveMotor_mode(MOTOR_BREAK);
			pl_L_DriveMotor_mode(MOTOR_BREAK);
			wait_ms_NoReset(500);
			straight_table2(-BACK_TO_CENTER-20/2, 0,0,-150,1000, mode);
			pl_R_DriveMotor_mode(MOTOR_BREAK);
			pl_L_DriveMotor_mode(MOTOR_BREAK);
			wait_ms_NoReset(500);
			no_safty = 0;
			clear_Ierror();
			maze_mode = 0;

			direction = direction + 2;

			if (direction >= 5) {
				direction = direction-4;
			}
			if (direction <= 0) {
				direction = direction+4;
			}

			break;
		}
		if(know_mode==0){
			kitikukan = 0;
		}
		if (kitikukan == OFF) {

			// 移動の優先順位 ： 前→右→左→後
			if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
			// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
				error_mode=1;
				pl_DriveMotor_stop();
				pl_DriveMotor_standby(OFF);
				break;
			}
			if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
				// 直進
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2(180/2-MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
			}
			if(right_count < front_count && right_count <= left_count && right_count <= back_count){
				// 右旋回
				slalomR(howspeed.slalom_R, OFF,EXPLORATION,0,input_StraightVelocity);
				direction++;
			}
			if(left_count < front_count && left_count < right_count && left_count <= back_count){
				// 左旋回
				slalomL(howspeed.slalom_L, OFF,EXPLORATION,0,input_StraightVelocity);
				direction--;
			}
			if(back_count < front_count && back_count < right_count
					&& back_count < left_count){
				//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2(90/2-MAZE_OFFSET-3, input_StraightVelocity,0,input_StraightVelocity,input_StraightAcceleration, mode);
				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(100);
				no_safty = 1;
				backTurn_controlWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
				//backTurn_hitWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
				wait_ms_NoReset(100);
				no_safty = 0;
				//clear_Ierror();
				mode.WallControlMode=0;
				straight_table2(-BACK_TO_CENTER, 0,0,-150,1000, mode);
				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(100);
				clear_Ierror();
				mode.WallControlMode=1;
				straight_table2(BACK_TO_CENTER +90/2,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				//straight_table2(BACK_TO_CENTER + 90,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				direction = direction + 2;

			}

		} else {
			mode.WallControlMode=1;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			straight_table2(90/2-MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
			compress_kitiku(&x,&y,&direction);
			mode.WallCutMode=0;
			End_straight(90/2-MAZE_OFFSET,mode,1,1);
			mode.WallControlMode=1;
			mode.calMazeMode=0;
			mode.WallCutMode=0;
			straight_table2((90/2 * kitiku_distance),input_StraightVelocity,input_StraightVelocity,900,input_StraightAcceleration, mode);

		}

		if (direction >= 5) {
			direction = direction-4;
		}
		if (direction <= 0) {
			direction = direction+4;
		}
//基地区間**********************************************************************
//		if (know_road == 1) {
//			most_speed_kitikukan_play(850, 1600);
//		}
//基地区間
		if(error_mode==1){break;}
		if (g_timCount_sec>240){
					// 秒数エンド
						timer_end_mode=1;
						pl_DriveMotor_stop();
						pl_DriveMotor_standby(OFF);
						break;
					}

	}
	if(error_mode==0){
	record_in();
	}
	create_DijkstraMap();
	clear_Ierror();
	reset_gyro();
	//reset_speed();
	maze_mode = 1;
	straight_table2(90/2+BACK_TO_CENTER,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

	while (1) {
		noGoalPillarMode=0;
		//straight_table2(90, 300, 300, 500);

		update_coordinate(&x,&y,direction);
		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){
			noGoalPillarMode=1;
		}else{
			noGoalPillarMode=0;
		}

		front_wall=(g_sensor_mean[SENSOR_FRONT] >= F_PRESENCE);
		right_wall=(g_sensor_mean[SENSOR_RIGHT] >= R_PRESENCE);
		left_wall=(g_sensor_mean[SENSOR_LEFT] >= L_PRESENCE);

		mode.WallControlMode=1;
		mode.calMazeMode=1;
		mode.WallCutMode=0;
		straight_table2(MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
		update_wall(x,y,direction,front_wall,right_wall,left_wall);
		if(Dijkstra_mode==1){
			route_Dijkstra();//ダイクストラ法の結果から最短ルートをスタックに入れる
			create_StepCountMap_unknown();
		}else{
			create_StepCountMapBack_queue();
		}
		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
		if (front_wall) {front_count = MAX_WALKCOUNT;}
		if (right_wall) {right_count = MAX_WALKCOUNT;}
		if (left_wall) {left_count = MAX_WALKCOUNT;}
		decision_kitiku(x,y,direction,front_count,right_count,back_count,left_count);
		mode.WallCutMode=1;
		End_straight(MAZE_OFFSET,mode,right_wall,left_wall);


			if(x == 0 && y == 0) {

				mode.WallControlMode=0;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2(90/2-MAZE_OFFSET, input_StraightVelocity,0,input_StraightVelocity,input_StraightAcceleration, mode);
				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(500);
				no_safty = 1;
				turning_table2(180,0,0,input_TurningVelocity,input_TurningAcceleration);
				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(500);
				straight_table2(-60/2, 0,0,-150,1000, mode);
				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(500);
				no_safty = 0;
				clear_Ierror();

				direction = direction + 2;

				if (direction >= 5) {
					direction = direction-4;
				}
				if (direction <= 0) {
					direction = direction+4;
				}

				break;
			}
			// 移動の優先順位 ： 前→右→左→後
			if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
			// 迷路破損のため停止.ダイクストラ法更新
				Dijkstra_maker_flag=1;
			}
			if (x<0 || y<0 || x>15 || y>15){
							// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
								error_mode=1;
								g_WallControl_mode=0;
								pl_yellow_LED_count(2*2*2*2);
								pl_DriveMotor_stop();
								pl_DriveMotor_standby(OFF);
								break;
			}


			if(Dijkstra_maker_flag==1){
				// 移動の優先順位 ： 前→右→左→後
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2(90/2-MAZE_OFFSET-(BACK_TO_CENTER-BACK_TO_CENTER_FRONT), input_StraightVelocity,0,input_StraightVelocity,input_StraightAcceleration, mode);

				pl_R_DriveMotor_mode(MOTOR_BREAK);
				pl_L_DriveMotor_mode(MOTOR_BREAK);
				wait_ms_NoReset(100);
				create_DijkstraMap();
				route_Dijkstra();//ダイクストラ法の結果から最短ルートをスタックに入れる
				create_StepCountMap_unknown();
				search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
				if (front_wall) {front_count = MAX_WALKCOUNT;}
				if (right_wall) {right_count = MAX_WALKCOUNT;}
				if (left_wall) {left_count = MAX_WALKCOUNT;}
								if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
								// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
									error_mode=1;
									g_WallControl_mode=0;
									pl_yellow_LED_count(2*2*2*2*2);
									pl_DriveMotor_stop();
									pl_DriveMotor_standby(OFF);
									break;
								}
								if (x<0 || y<0 || x>15 || y>15){
								// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
									error_mode=1;
									g_WallControl_mode=0;
									pl_yellow_LED_count(2*2*2*2);
									pl_DriveMotor_stop();
									pl_DriveMotor_standby(OFF);
									break;
								}
								mode.WallControlMode=0;
								mode.WallCutMode=0;
								mode.calMazeMode=0;
								if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
									// 直進
									straight_table2(90/2+(BACK_TO_CENTER-BACK_TO_CENTER_FRONT), 0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
								}
								if(right_count < front_count && right_count <= left_count && right_count <= back_count){
									// 右旋回
									turning_table2(-90,0,0,-input_TurningVelocity,input_TurningAcceleration);
									pl_R_DriveMotor_mode(MOTOR_BREAK);
									pl_L_DriveMotor_mode(MOTOR_BREAK);
									wait_ms_NoReset(100);
									straight_table2(90/2+(BACK_TO_CENTER-BACK_TO_CENTER_FRONT), 0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
									direction++;
								}
								if(left_count < front_count && left_count < right_count && left_count <= back_count){
									// 左旋回
									turning_table2(90,0,0,input_TurningVelocity,input_TurningAcceleration);
									pl_R_DriveMotor_mode(MOTOR_BREAK);
									pl_L_DriveMotor_mode(MOTOR_BREAK);
									wait_ms_NoReset(100);
									straight_table2(90/2+(BACK_TO_CENTER-BACK_TO_CENTER_FRONT), 0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
									direction--;
								}
								if(back_count < front_count && back_count < right_count
										&& back_count < left_count){
									//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
									no_safty = 1;
									backTurn_controlWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
									//backTurn_hitWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
									wait_ms_NoReset(100);
									no_safty = 0;
									//clear_Ierror();
									mode.WallControlMode=0;
									if(front_wall){
									straight_table2(-BACK_TO_CENTER, 0,0,-150,1000, mode);
									pl_R_DriveMotor_mode(MOTOR_BREAK);
									pl_L_DriveMotor_mode(MOTOR_BREAK);
									wait_ms_NoReset(100);

									clear_Ierror();
									mode.WallControlMode=1;
									straight_table2(BACK_TO_CENTER +90/2,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
									}else{
										clear_Ierror();
										mode.WallControlMode=0;
										straight_table2(90/2+(BACK_TO_CENTER-BACK_TO_CENTER_FRONT),0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

									}
									//straight_table2(BACK_TO_CENTER + 90,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
									direction = direction + 2;

								}


			}else{

				if(know_mode==0){
					kitikukan = 0;
				}
			if (kitikukan == OFF) {


				if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
					// 直進
					mode.WallControlMode=1;
					mode.calMazeMode=0;
					mode.WallCutMode=0;
					straight_table2(180/2-MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				}
				if(right_count < front_count && right_count <= left_count && right_count <= back_count){
					// 右旋回
					slalomR(speed300_exploration.slalom_R, OFF,EXPLORATION,0,input_StraightVelocity);
					direction++;
				}
				if(left_count < front_count && left_count < right_count && left_count <= back_count){
					// 左旋回
					slalomL(speed300_exploration.slalom_L, OFF,EXPLORATION,0,input_StraightVelocity);
					direction--;
				}
				if(back_count < front_count && back_count < right_count
						&& back_count < left_count){
					//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
					//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
					mode.WallControlMode=1;
					mode.calMazeMode=0;
					mode.WallCutMode=0;
					straight_table2(90/2-MAZE_OFFSET, input_StraightVelocity,0,input_StraightVelocity,input_StraightAcceleration, mode);
					pl_R_DriveMotor_mode(MOTOR_BREAK);
					pl_L_DriveMotor_mode(MOTOR_BREAK);
					wait_ms_NoReset(100);
					create_DijkstraMap();
					no_safty = 1;
					backTurn_controlWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
					//backTurn_hitWall(input_TurningVelocity, input_TurningAcceleration, front_wall, left_wall, right_wall);
					wait_ms_NoReset(100);
					no_safty = 0;
					//clear_Ierror();
					mode.WallControlMode=0;
					if(front_wall){
					straight_table2(-BACK_TO_CENTER, 0,0,-150,1000, mode);
					pl_R_DriveMotor_mode(MOTOR_BREAK);
					pl_L_DriveMotor_mode(MOTOR_BREAK);
					wait_ms_NoReset(100);

					clear_Ierror();
					mode.WallControlMode=1;
					straight_table2(BACK_TO_CENTER +90/2,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
					}else{
						clear_Ierror();
						mode.WallControlMode=0;
						straight_table2(90/2,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);

					}
					//straight_table2(BACK_TO_CENTER + 90,0,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
					direction = direction + 2;

				}

			} else {
				mode.WallControlMode=1;
				mode.calMazeMode=1;
				mode.WallCutMode=0;
				straight_table2(90/2-MAZE_OFFSET, input_StraightVelocity,input_StraightVelocity,input_StraightVelocity,input_StraightAcceleration, mode);
				compress_kitiku(&x,&y,&direction);
				mode.WallCutMode=0;
				End_straight(90/2-MAZE_OFFSET,mode,1,1);
				mode.WallControlMode=1;
				mode.calMazeMode=0;
				mode.WallCutMode=0;
				straight_table2((90/2 * kitiku_distance),input_StraightVelocity,input_StraightVelocity,1000,input_StraightAcceleration, mode);

			}
			}

			if (direction >= 5) {
				direction = direction-4;
			}
			if (direction <= 0) {
				direction = direction+4;
			}
	//基地区間**********************************************************************
	//		if (know_road == 1) {
	//			most_speed_kitikukan_play(850, 1600);
	//		}
	//基地区間
			if(error_mode==1){break;}
			if (g_timCount_sec>240){
						// 秒数エンド
							timer_end_mode=1;
							pl_DriveMotor_stop();
							pl_DriveMotor_standby(OFF);
							break;
						}
		}

	pl_DriveMotor_standby(OFF); //MTU2.TSTR.BIT.CST0 = 0;
	maze_mode = 0;
	HAL_Delay(100);
	maze_display();
	create_StepCountMap_queue();
	if(walk_count[0][0] == 255){
		error_mode = 1;
	}
	if (error_mode == 0) {
		record_in();
	} else if(timer_end_mode==0) {
		record_out();
	}else{
		record_in();
	}

}




void pass_maker(void){
	unsigned short front_count, right_count, back_count, left_count;

	_Bool front_wall;
	_Bool right_wall;
	_Bool left_wall;

	int x = 0;
	int y = 0;
	int direction = 1;
	pass_count = 0;
	create_StepCountMap_queue();
	//maze_makerST(stmass);
	maze_display();
	pass[0] = 1;
	while (1) {
//		if (mode_safty == 1) {break;}
		update_coordinate(&x,&y,direction);

		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){

			if (pass[pass_count] >= 0) {
					} else {
						pass_count++;
					}
					pass[pass_count] = pass[pass_count] + 1;
		//			wait(10);
		//			maze_display();
		//			x = 0;
		//			y = 0;
					direction = direction + 2;
					if (direction == 5) {
						direction = 1;
					}
					if (direction == 6) {
						direction = 2;
					}
					if (direction == 0) {
						direction = 4;
					}
					if (direction == -1) {
						direction = 3;
					}
					break;

		}

		get_wall(x,y,direction,&front_wall,&right_wall,&left_wall);
		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
		if (front_wall) {front_count = MAX_WALKCOUNT;}
		if (right_wall) {right_count = MAX_WALKCOUNT;}
		if (left_wall) {left_count = MAX_WALKCOUNT;}

		if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
			// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
			pl_play_oneSound(1);
			break;
		}
		if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
			// 直進
			if (pass[pass_count] >= 0) {} else {pass_count++;}
			pass[pass_count] = pass[pass_count] + 2;
		}
		if(right_count < front_count && right_count <= left_count && right_count <= back_count){
			// 右旋回
			pass_count++;
			pass[pass_count] = -2;
			direction++;
		}
		if(left_count < front_count && left_count < right_count && left_count <= back_count){
			// 左旋回
			pass_count++;
			pass[pass_count] = -3;
			direction--;
		}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

	}
}





void pass_maker_Dijkstra(void){

	unsigned short front_count, right_count, back_count, left_count;

	_Bool front_wall;
	_Bool right_wall;
	_Bool left_wall;

	int x = 0;
	int y = 0;
	int direction = 1;
	pass_count = 0;
	create_DijkstraMap();
	maze_display_Dijkstra();
	pass[0] = 1;
	while (1) {
//		if (mode_safty == 1) {break;}
		update_coordinate(&x,&y,direction);

		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){

			if (pass[pass_count] >= 0) {
					} else {
						pass_count++;
					}
					pass[pass_count] = pass[pass_count] + 1;
		//			wait(10);
		//			maze_display();
		//			x = 0;
		//			y = 0;
					direction = direction + 2;
					if (direction == 5) {
						direction = 1;
					}
					if (direction == 6) {
						direction = 2;
					}
					if (direction == 0) {
						direction = 4;
					}
					if (direction == -1) {
						direction = 3;
					}
					break;

		}

		get_wall(x,y,direction,&front_wall,&right_wall,&left_wall);
		search_AroundDijkstraCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
		if (front_wall) {front_count = MAX_WALKCOUNT_DIJKSTRA;}
		if (right_wall) {right_count = MAX_WALKCOUNT_DIJKSTRA;}
		if (left_wall) {left_count = MAX_WALKCOUNT_DIJKSTRA;}

		if (front_count==MAX_WALKCOUNT_DIJKSTRA && right_count==MAX_WALKCOUNT_DIJKSTRA && left_count==MAX_WALKCOUNT_DIJKSTRA && back_count==MAX_WALKCOUNT_DIJKSTRA){
			// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)

			break;
		}
		if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
			// 直進
			if (pass[pass_count] >= 0) {} else {pass_count++;}
			pass[pass_count] = pass[pass_count] + 2;
		}
		if(right_count < front_count && right_count <= left_count && right_count <= back_count){
			// 右旋回
			pass_count++;
			pass[pass_count] = -2;
			direction++;
		}
		if(left_count < front_count && left_count < right_count && left_count <= back_count){
			// 左旋回
			pass_count++;
			pass[pass_count] = -3;
			direction--;
		}

		if (direction == 5) {
			direction = 1;
		}
		if (direction == 6) {
			direction = 2;
		}
		if (direction == 0) {
			direction = 4;
		}
		if (direction == -1) {
			direction = 3;
		}

	}
}


void run_shortest(float inspeed, float inacc, int stmass, char pass_mode, char fun_mode,
		char slant_mode, parameter_speed howspeed,float fun_ratio,char mollifier_mode) {
	unsigned char slant_count;
	int slant_direction;
	float first_v,last_v;
	float end_velocity;

//	unsigned short front_count, right_count, back_count, left_count;
//
//	_Bool front_wall;
//	_Bool right_wall;
//	_Bool left_wall;
//
//	int x = 0;
//	int y = 0;
//	int direction = 1;
	slant_direction = -2;

	MOTOR_MODE mode;
	mode.WallControlMode=1;
	mode.WallControlStatus=0;
	mode.WallCutMode=0;
	mode.calMazeMode=0;

	//highspeed_mode = 1;
	for(int i = 0; i <= 254; i++){pass[i] = 0;}
	for(int i = 0; i <= 14; i++){
		record.row[i] = wall.row[i];
		record.column[i] = wall.column[i];
		record.row_look[i] = wall.row_look[i];
		record.column_look[i] = wall.column_look[i];
		wall.row_look[i] = ~wall.row_look[i];
		wall.column_look[i] = ~wall.column_look[i];
		wall.row[i] = wall.row[i] | wall.row_look[i];
		wall.column[i] = wall.column[i] | wall.column_look[i];
	}
	//pass_maker();
   pass_maker_Dijkstra();

	pass_count = 1;
if(pass_mode==1){
	while (1) {		//パス圧縮
//		if (mode_safty == 1) {
//
//			break;
//		}
		if (pass[pass_count] == 0) {
			break;
		}

		if (pass[pass_count] == -2 && pass[pass_count - 1] >= 1	//右90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -4;		//右90度大回り

		}
		if (pass[pass_count] == -3 && pass[pass_count - 1] >= 1	//左90度大回りの条件
		&& pass[pass_count + 1] >= 1) {
			pass[pass_count - 1] = pass[pass_count - 1] - 1;	//前90直進の削除
			pass[pass_count + 1] = pass[pass_count + 1] - 1;	//後90直進の削除
			pass[pass_count] = -5;		//左90度大回り

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -2
				&& pass[pass_count + 1] == -2 && pass[pass_count + 2] >= 1) {//右180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -6;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;

		}
		if (pass[pass_count - 1] >= 1 && pass[pass_count] == -3
				&& pass[pass_count + 1] == -3 && pass[pass_count + 2] >= 1) {//左180度大回りの条件
			pass[pass_count - 1] = pass[pass_count - 1] - 1;
			pass[pass_count] = -7;
			pass[pass_count + 1] = -1;
			pass[pass_count + 2] = pass[pass_count + 2] - 1;
		}
		if (pass[pass_count] == -2 && pass[pass_count - 1] == -3	//左90度大回りの条件

				) {
		}
//		if(){}
		if (pass[pass_count - 1] == 0) {
			pass[pass_count - 1] = -1;		//passが0になってしまったときの対策
		}

		pass_count++;
	}

	pass_count = 1;
	if (slant_mode == 1) {
		while (1) {		//斜め入出の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count - 1] >= 1) {
				if (pass[pass_count] == -2 || pass[pass_count] == -3) {
//***************************************************************************************入りのモーションstart
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -8;		//右45
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -9;		//左45
					}
					if (pass[pass_count] == -2 && pass[pass_count + 1] == -2) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -10;		//右135
						pass[pass_count + 1] = -1;
					}
					if (pass[pass_count] == -3 && pass[pass_count + 1] == -3) {
						pass[pass_count - 1] = pass[pass_count - 1] - 1;
						if (pass[pass_count - 1] == 0) {
							pass[pass_count - 1] = -1;	//passが0になってしまったときの対策
						}
						pass[pass_count] = -11;		//左135
						pass[pass_count + 1] = -1;
					}
//***************************************************************************************入りのモーションend

//***************************************************************************************途中のモーションstart
					while (pass[pass_count] <= -1) {
						pass_count++;
					}
//***************************************************************************************途中のモーションend

//***************************************************************************************出のモーションstart
					if (pass[pass_count - 1] == -2) {
						if (pass[pass_count - 2] == -2) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -14;		//右135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -12;		//右45
						}

					}
					if (pass[pass_count - 1] == -3) {
						if (pass[pass_count - 2] == -3) {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -15;		//左135
							pass[pass_count - 2] = -1;
						} else {
							pass[pass_count] = pass[pass_count] - 1;
							if (pass[pass_count] == 0) {
								pass[pass_count] = -1;	//passが0になってしまったときの対策
							}
							pass[pass_count - 1] = -13;		//左45
						}

					}
//***************************************************************************************出のモーションend
				}
			}
			//		if(){}

			pass_count++;
		}

		pass_count = 1;
		while (1) {		//斜の圧縮
			if (pass[pass_count] == 0) {
				break;
			}

			if (pass[pass_count] == -8 || pass[pass_count] == -9
					|| pass[pass_count] == -10 || pass[pass_count] == -11) {
				if (pass[pass_count] == -8 || pass[pass_count] == -10) {
					slant_direction = -3;
				}
				if (pass[pass_count] == -9 || pass[pass_count] == -11) {
					slant_direction = -2;
				}
				pass_count++;
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
					pass_count++;
				}
				if (pass[pass_count] >= -3) {
					slant_count = pass_count;
					pass[slant_count] = 51;
					pass_count++;
				}

				//***************************************************************************************途中のモーションstart
				while (pass[pass_count] >= -3) {
					if (pass[pass_count] == -1) {		//135ターンようのー１を進めるため
						pass_count++;
					}
					if (pass[pass_count] == -12 || pass[pass_count] == -13
							|| pass[pass_count] == -14
							|| pass[pass_count] == -15) {
						break;
					}
					if (pass[pass_count] == slant_direction) {
						pass[slant_count] = pass[slant_count] - 1;
						slant_count = pass_count;
						if (slant_direction == -2) {
							pass[pass_count] = -16;
						}
						if (slant_direction == -3) {
							pass[pass_count] = -17;
						}

					} else {
						if (pass[slant_count] >= 50) {
							pass[pass_count] = -1;
						} else {
							slant_count = pass_count;
							pass[slant_count] = 50;
						}
						pass[slant_count] = pass[slant_count] + 1;
						if (slant_direction == -2) {
							slant_direction = -3;
						} else {
							slant_direction = -2;
						}

					}

					pass_count++;
				}
				//***************************************************************************************途中のモーションend

			}

			//		if(){}

			pass_count++;
		}
		pass_count=0;
		while (1) {		//パス圧縮

			if (pass[pass_count] == 50) {
				pass[pass_count] =-1;

			}
			if (pass[pass_count] == 0) {
				break;
			}
			pass_count++;
		}

	}
}
	int j = 0;
	while (pass[j] != 0) {
		printf("pass_count %d pass %d\n", j, pass[j]);
		j++;
	}
	int pass_count2;
	pass_count2=0;
	while(pass[pass_count2] == -1){
		pass_count2++;
	}
	end_velocity=get_center_velocity(howspeed,pass[pass_count2]);
	printf("%d,%f\n",pass_count2, end_velocity);

	HAL_Delay(500);
	pl_DriveMotor_standby(ON);
	pl_R_DriveMotor_mode(MOTOR_BREAK);
	pl_L_DriveMotor_mode(MOTOR_BREAK);
	wait_ms_NoReset(500);
	no_safty = 1;
	no_safty = 0;
	clear_Ierror();
	////wall_control_mode = 1;
	if (fun_mode == 1) {
		pl_FunMotor_duty(fun_ratio*BATT_MAX/g_V_battery_mean);
		pl_FunMotor_start();
		HAL_Delay(600);
		reset_gyro();
		reset_speed();
		clear_Ierror();
//		HAL_Delay(1000);
//				reset_gyro();
//				enc.sigma_error = 0;
//					Gyro.sigma_error = 0;
//				pl_FunMotor_duty(160);
//		pl_FunMotor_start();
//						HAL_Delay(2000);	//候補1

	}
	maze_mode = 1;
	highspeed_mode = 1;
//	record_mode=14;
	record_mode=18;
//	encoder_PID_error=2500;
//	gyro_PID_error=1800;
	wall_control = 0;
	pass_count = 0;


	mode.WallControlMode=1;
	mode.WallControlStatus=0;
	mode.calMazeMode=0;
	mode.WallCutMode=0;
	pass_count2=0;
	while(pass[pass_count2] == -1){
		pass_count2++;
	}
	end_velocity=get_center_velocity(howspeed,pass[pass_count2]);
	straight_table2(BACK_TO_CENTER_FRONT,0,end_velocity,end_velocity,end_velocity*end_velocity/ BACK_TO_CENTER_FRONT/2, mode);


	while (pass_count <= 255) {
		pass_count2=pass_count+1;
		while(pass[pass_count2] == -1){
			pass_count2++;
		}
		end_velocity=get_center_velocity(howspeed,pass[pass_count2]);

		if (pass[pass_count] == -1) {
			pass_count++;
		}
		else if (pass[pass_count] == -2) {

			slalomR(howspeed.slalom_R, OFF,SHORTEST,mollifier_mode,end_velocity);

			pass_count++;
		}
		else if (pass[pass_count] == -3) {

			slalomL(howspeed.slalom_L, OFF,SHORTEST,mollifier_mode,end_velocity);

			pass_count++;
		}
		else if (pass[pass_count] == -4) {
			turn90R(howspeed.turn90_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -5) {
			turn90L(howspeed.turn90_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -6) {
			turn180R(howspeed.turn180_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -7) {
			turn180L(howspeed.turn180_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -8) { //入り45R
			turn45inR(howspeed.turn45in_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -9) { //入り45L
			turn45inL(howspeed.turn45in_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -10) { //入り135R
			turn135inR(howspeed.turn135in_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -11) { //入り135L
			turn135inL(howspeed.turn135in_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -12) { //出り45R
			turn45outR(howspeed.turn45out_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -13) { //出り45L
			turn45outL(howspeed.turn45out_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -14) { //出り135R
			turn135outR(howspeed.turn135out_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -15) { //出り135L
			turn135outL(howspeed.turn135out_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -16) { //V90R
			V90R(howspeed.V90_R, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] == -17) { //V90L
			V90L(howspeed.V90_L, OFF,mollifier_mode,end_velocity);
			pass_count++;
		}
		else if (pass[pass_count] >= 1) {
			first_v = howspeed.TurnCentervelocity;
			last_v = howspeed.TurnCentervelocity;
			if (pass_count >= 1) {

				if (pass[pass_count - 1] == -2 || pass[pass_count - 1] == -3) {
					first_v = howspeed.SlalomCentervelocity;
				}
			}
			if (pass[pass_count + 1] == -2 || pass[pass_count + 1] == -3) {
				last_v = howspeed.SlalomCentervelocity;
			}
			if (pass[pass_count] >= 50) {
				mode.WallControlMode=3;
				mode.WallControlStatus=0;
				straight_table2((45 * sqrt(2) * (pass[pass_count] - 50)),first_v, end_velocity,inspeed, inacc, mode);
			} else {
				mode.WallControlMode=1;
				mode.WallControlStatus=0;
				straight_table2((45 * pass[pass_count]),first_v, end_velocity,inspeed, inacc, mode);
			}

			pass_count++;
		}

		if (pass[pass_count] == 0) {
			break;
		}


//		if (mode_safty == 1) {
//
//			break;
//		}
	}

		mode.WallControlMode=1;
		mode.WallControlStatus=0;
		straight_table2(90,end_velocity, 0,inspeed, inacc, mode);
		HAL_Delay(700);
		pl_FunMotor_stop();
//		turning_table(180, 0, 0, 400, 5000);

	maze_mode = 0;
	highspeed_mode = 0;
	record_mode=0;
	pl_DriveMotor_standby(OFF);
	t = 0;

	while (t <= 14) {
		wall.row[t] = record.row[t];
		wall.column[t] = record.column[t];
		t++;
	}
	t = 0;
	while (t <= 14) {
		wall.row_look[t] = ~wall.row_look[t];
		wall.column_look[t] = ~wall.column_look[t];
		t++;
	}

}











void decision_kitiku(int x,int y,int direction,unsigned short front_count,unsigned short right_count,unsigned short back_count,unsigned short left_count){
	_Bool front_wall=1;
	_Bool right_wall=1;
	_Bool left_wall=1;
	int x_front=x;
	int y_front=y;
	update_coordinate(&x_front,&y_front,direction);
	get_wall_look(x_front,y_front,direction,&front_wall,&right_wall,&left_wall);
	_Bool look_f=(front_wall && right_wall && left_wall);

	//ここに壁条件がない
	if (look_f && front_count <= right_count
			&& front_count <= left_count && front_count <= back_count) {
		if ((direction==1 && y>=14) ||
			(direction==2 && x>=14) ||
			(direction==3 && y<=1) ||
			(direction==4 && x<=1) ){
			kitikukan = 0;
		}else{
			kitikukan = 1;
		}

	} else {
		kitikukan = 0;
	}


}

void compress_kitiku(int *x,int *y,int *direction) {
	kitiku_distance = 1;
	kitiku = 1;
	_Bool front_wall;
	_Bool right_wall;
	_Bool left_wall;
	_Bool look_f,look_r,look_l;
	int x_now,y_now,direction_now;
	int x_front,y_front,x_right,y_right,x_left,y_left;
	int direction_right,direction_left;
	unsigned short front_count, right_count, back_count, left_count;
	x_now=*x;y_now=*y;direction_now=*direction;
	while (1) {
		update_coordinate(&x_now,&y_now,direction_now);
		x_front=x_now;y_front=y_now;x_right=x_now;y_right=y_now;x_left=x_now;y_left=y_now;

		update_coordinate(&x_front,&y_front,direction_now);
		get_wall_look(x_front,y_front,direction_now,&front_wall,&right_wall,&left_wall);
		look_f=(front_wall && right_wall && left_wall);


		if(direction_now==4){direction_right=1;}else{direction_right=direction_now+1;}
		update_coordinate(&x_right,&y_right,direction_right);
		get_wall_look(x_right,y_right,direction_right,&front_wall,&right_wall,&left_wall);
		look_r=(front_wall && right_wall && left_wall);


		if(direction_now==1){direction_left=4;}else{direction_left=direction_now-1;}
		update_coordinate(&x_left,&y_left,direction_left);
		get_wall_look(x_left,y_left,direction_left,&front_wall,&right_wall,&left_wall);
		look_l=(front_wall && right_wall && left_wall);

		get_wall(x_now,y_now,direction_now,&front_wall,&right_wall,&left_wall);

		search_AroundWalkCount(&front_count,&right_count,&back_count,&left_count,x_now,y_now,direction_now);
		if (front_wall) {front_count = MAX_WALKCOUNT;}
		if (right_wall) {right_count = MAX_WALKCOUNT;}
		if (left_wall) {left_count = MAX_WALKCOUNT;}
		// 移動の優先順位 ： 前→右→左→後
		if (walk_count[x_now][y_now] <= 1) {
			//goal間近で停止
			break;
		}
		if (direction_now==1 && y_now>=14) {break;}
		if (direction_now==2 && x_now>=14) {break;}
		if (direction_now==3 && y_now<=1) {break;}
		if (direction_now==4 && x_now<=1) {break;}
		if (front_count==MAX_WALKCOUNT && right_count==MAX_WALKCOUNT && left_count==MAX_WALKCOUNT && back_count==MAX_WALKCOUNT){
		// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)
			error_mode=1;
		break;
		}
		if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
		// 直進
			if(look_f){
				kitiku_distance += 2;
			}else{
				kitiku = 0;
				break;
			}
		}
		if(right_count < front_count && right_count <= left_count && right_count <= back_count){
		// 右旋回
			if(look_r){
				kitiku = 0;
				break;
			}else{
				kitiku = 0;
				break;
			}
			direction_now++;
		}
		if(left_count < front_count && left_count < right_count && left_count <= back_count){
		// 左旋回
			if(look_l){
				kitiku = 0;
				break;
			}else{
				kitiku = 0;
				break;
			}
			direction_now--;
		}
		if(back_count < front_count && back_count < right_count
								&& back_count < left_count){
		//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
		//180度旋回(前壁がある場合は尻当てを行うことで位置修正)
			kitiku = 0;
			break;
			direction_now+=2;
		}


		if (direction_now == 5) {
			direction_now = 1;
		}
		if (direction_now == 6) {
			direction_now = 2;
		}
		if (direction_now == 0) {
			direction_now = 4;
		}
		if (direction_now == -1) {
			direction_now = 3;
		}
		if (kitiku == 0) {

			break;
		}

	}

	int direction2=direction_now+2;
	if (direction2 == 5) {
				direction2 = 1;
			}
			if (direction2 == 6) {
				direction2 = 2;
			}
			if (direction2 == 0) {
				direction2 = 4;
			}
			if (direction2 == -1) {
				direction2 = 3;
			}

	update_coordinate(&x_now,&y_now,direction2);

	*x=x_now;
	*y=y_now;
	*direction=direction_now;

}

