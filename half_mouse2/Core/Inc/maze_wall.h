/*
 * maze_wall.h
 *
 *  Created on: 2023/06/29
 *      Author: sf199
 */

#ifndef INC_MAZE_WALL_H_
#define INC_MAZE_WALL_H_

#include"main.h"


#define MAX_QUEUE_NUM 350

#define COLUMN 0
#define ROW 1

#define MAX_WALKCOUNT_DIJKSTRA 65535

#define VERTICALCOST 180
#define DIAGONALCOST 127
#define MIN_VERTICALCOST 12
#define MIN_DIAGONALCOST 10
#define DISCOUNTCOST_V 1//絶対1
#define DISCOUNTCOST_D 1//絶対1
#define V_NUM_MAX 5
#define D_NUM_MAX 6

#define SLANT_NORTH 0
#define SLANT_NORTH_EAST 1
#define SLANT_EAST 2
#define SLANT_SOUTH_EAST 3
#define SLANT_SOUTH 4
#define SLANT_SOUTH_WEST 5
#define SLANT_WEST 6
#define SLANT_NORTH_WEST 7


typedef struct{
	uint16_t row[15];
	uint16_t column[15];
	uint16_t row_look[15];
	uint16_t column_look[15];

}WALL;

typedef struct{
	uint16_t row_count[16][15];
	uint16_t column_count[16][15];
}DIJKSTRA;

// スタック構造体
typedef struct{
	/* データの最前列 */
	int head;
    /* データの最後尾 */
    int tail;
    /* スタックされているデータ */
    int data[MAX_QUEUE_NUM];
} STACK_T;

extern WALL wall;
extern WALL record;





extern unsigned short walk_count[256]; //歩数いれる箱



void maze_clear();
void update_wall(int,int,int,_Bool,_Bool,_Bool);
void get_wall(int,int,int,_Bool*,_Bool*,_Bool*);
void get_wall_look(int,int,int,_Bool*,_Bool*,_Bool*);

void search_AroundWalkCount(unsigned short *,unsigned short *,unsigned short *,unsigned short *,int,int,int);
void search_AroundDijkstraCount(unsigned short *,unsigned short *,unsigned short *,unsigned short *,int,int,int);

void create_StepCountMap();
void create_StepCountMapBack();

void route_Dijkstra();
void create_DijkstraMap();
void create_StepCountMap_unknown();

void create_StepCountMap_queue();
void create_StepCountMapBack_queue();
void initStack_walk(STACK_T *);
void pushStack_walk(STACK_T *, unsigned short);
unsigned short popStack_walk(STACK_T *);
void create_StepCountMap_ST(int);


void maze_maker(int,int,int,int,int,int);
void maze_maker2(int,int,int,int,int,int);
void maze_makerhosuu(int,int,int);

void maze_makerRun(int,int,int,int,int,int);
void maze_makeronly(int,int,int,int,int,int);
void maze_makerback(int,int,int,int,int,int);

void maze_display();
void maze_display_Dijkstra();


#endif /* INC_MAZE_WALL_H_ */
