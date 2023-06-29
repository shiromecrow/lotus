/*
 * maze_strategy.h
 *
 *  Created on: 2023/06/29
 *      Author: sf199
 */

#ifndef INC_MAZE_STRATEGY_H_
#define INC_MAZE_STRATEGY_H_

#include "turning_parameter.h"

#define TURN_ON 1
#define TURN_OFF 0
#define FUN_ON 1
#define FUN_OFF 0
#define SLANT_ON 1
#define SLANT_OFF 0

int x;
int y;
int wall_control;
int SENF_maze, SENR_maze, SENL_maze;
int direction;


char maze_mode;
int kitikukan;




int pass[255]; //1f 2r 3l
//unsigned short front_count;
//unsigned short left_count;
//unsigned short right_count;
//unsigned short back_count;
//unsigned short walk_count[256];
//unsigned short row[15];
//unsigned short column[15];
//unsigned short row_look[15];
//unsigned short column_look[15];
int gg;


void record_in(void);
void record_out(void);

void left_way(void);

void decision_kitiku(int,int,int,unsigned short,unsigned short,unsigned short,unsigned short);
void compress_kitiku(int *,int *,int *);

void update_coordinate(int *,int *,int);
void AdatiWayReturn(float,float,float,float, parameter_speed,int,uint8_t);

void pass_maker();
void pass_maker_Dijkstra();

void run_shortest(float,float,int,char,char,char,parameter_speed,float,char);


void adati_wayreturnSL(float,float,float,float,float,float,float,float,float,float,float,float,float);
void adati_wayonlybackSL(float,float,float,float,float,float,float,float,float,float,float,float,float,int);


#endif /* INC_MAZE_STRATEGY_H_ */
