/*
 * maze_wall.c
 *
 *  Created on: 2023/06/29
 *      Author: sf199
 */


#include "maze_wall.h"
#include"maze_strategy.h"
#include"define.h"


WALL wall;
WALL record;

char Dijkstra_maker_flag;

uint16_t walk_count[16][16]; //歩数いれる箱
DIJKSTRA Dijkstra;
STACK_T g_Goal_x;
STACK_T g_Goal_y;

int tt = 0;
int ss = 0;
int mode_255 = 0;
unsigned char Xend_cheak = 240; //x終わりの判定240
unsigned char Yend_cheak = 15; //y終わりの判定15




unsigned char coordinate; //座標
unsigned short count_number; //歩数の値

unsigned char Xcheak_result;
unsigned char Ycheak_result;
unsigned char Xcoordinate;
unsigned char Ycoordinate;
unsigned short wall_north;
unsigned short wall_south;
unsigned short wall_east;
unsigned short wall_west;
unsigned short front_count;
unsigned short left_count;
unsigned short right_count;
unsigned short back_count;



void maze_clear(void) { //初期化

	Dijkstra_maker_flag=0;
	tt = 0;
	while (tt <= 14) {
		wall.row[tt] = 0;
		wall.column[tt] = 0;
		wall.row_look[tt] = 0;
		wall.column_look[tt] = 0;
		tt++;
	}
	tt = 0;


	for(int i=0;i<=15;i++){
		for(int j=0;j<=14;j++){
			Dijkstra.column_count[i][j]=65535;
			Dijkstra.row_count[i][j]=65535;
		}
	}
	Dijkstra.column_count[GOAL_X][GOAL_Y]=0;
	Dijkstra.column_count[GOAL_X+1][GOAL_Y]=0;
	Dijkstra.row_count[GOAL_Y][GOAL_X]=0;
	Dijkstra.row_count[GOAL_Y+1][GOAL_X]=0;


//ここから歩数マップの初期状態を作る．
create_StepCountMap_queue();

//kokomade

}



void update_wall(int x,int y,int direction,_Bool front_wall,_Bool right_wall,_Bool left_wall){
// x:x座標, y:y座標, direction:向き(北1東2南3西4),
//front_wall:前壁の有無(Ture=1 false=0), right_wall:右壁の有無(Ture=1 false=0), left_wall:左壁の有無(Ture=1 false=0)

	switch (direction) {
	case 1:
		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(front_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(left_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(right_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		break;
	case 2:
		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(front_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(left_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(right_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		break;
	case 3:
		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(front_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		if (x <= 14) {
			wall.row_look[x] = wall.row_look[x] | (1 << y);
			if(left_wall){wall.row[x] = wall.row[x] | (1 << y);}
		}

		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(right_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		break;
	case 4:
		if (x >= 1) {
			wall.row_look[x - 1] = wall.row_look[x - 1] | (1 << y);
			if(front_wall){wall.row[x - 1] = wall.row[x - 1] | (1 << y);}
		}

		if (y >= 1) {
			wall.column_look[y - 1] = wall.column_look[y - 1] | (1 << x);
			if(left_wall){wall.column[y - 1] = wall.column[y - 1] | (1 << x);}
		}

		if (y <= 14) {
			wall.column_look[y] = wall.column_look[y] | (1 << x);
			if(right_wall){wall.column[y] = wall.column[y] | (1 << x);}
		}

		break;

	}


}



void get_wall(int x,int y,int direction,_Bool* front_wall,_Bool* right_wall,_Bool* left_wall){
	*front_wall=1;
	*right_wall=1;
	*left_wall=1;
	switch (direction) {
	case 1:
		if (y <= 14) {
			*front_wall=((wall.column[y] & (1 << x)) == (1 << x));
		}
		if (x >= 1) {
			*left_wall=((wall.row[x - 1] & (1 << y)) == (1 << y));
		}
		if (x <= 14) {
			*right_wall=((wall.row[x] & (1 << y)) == (1 << y));
		}
		break;
	case 2:
		if (x <= 14) {
			*front_wall=((wall.row[x] & (1 << y)) == (1 << y));
		}
		if (y <= 14) {
			*left_wall=((wall.column[y] & (1 << x)) == (1 << x));
		}
		if (y >= 1) {
			*right_wall=((wall.column[y - 1] & (1 << x)) == (1 << x));
		}
		break;
	case 3:
		if (y >= 1) {
			*front_wall=((wall.column[y - 1] & (1 << x)) == (1 << x));
		}
		if (x <= 14) {
			*left_wall=((wall.row[x] & (1 << y)) == (1 << y));
		}
		if (x >= 1) {
			*right_wall=((wall.row[x - 1] & (1 << y)) == (1 << y));
		}
		break;
	case 4:
		if (x >= 1) {
			*front_wall=((wall.row[x - 1] & (1 << y)) == (1 << y));
		}
		if (y >= 1) {
			*left_wall=((wall.column[y - 1] & (1 << x)) == (1 << x));
		}
		if (y <= 14) {
			*right_wall=((wall.column[y] & (1 << x)) == (1 << x));
		}
		break;
	}

}


void get_wall_look(int x,int y,int direction,_Bool* front_wall,_Bool* right_wall,_Bool* left_wall){
	*front_wall=1;
	*right_wall=1;
	*left_wall=1;
	switch (direction) {
	case 1:
		if (y <= 14) {
			*front_wall=((wall.column_look[y] & (1 << x)) == (1 << x));
		}
		if (x >= 1) {
			*left_wall=((wall.row_look[x - 1] & (1 << y)) == (1 << y));
		}
		if (x <= 14) {
			*right_wall=((wall.row_look[x] & (1 << y)) == (1 << y));
		}
		break;
	case 2:
		if (x <= 14) {
			*front_wall=((wall.row_look[x] & (1 << y)) == (1 << y));
		}
		if (y <= 14) {
			*left_wall=((wall.column_look[y] & (1 << x)) == (1 << x));
		}
		if (y >= 1) {
			*right_wall=((wall.column_look[y - 1] & (1 << x)) == (1 << x));
		}
		break;
	case 3:
		if (y >= 1) {
			*front_wall=((wall.column_look[y - 1] & (1 << x)) == (1 << x));
		}
		if (x <= 14) {
			*left_wall=((wall.row_look[x] & (1 << y)) == (1 << y));
		}
		if (x >= 1) {
			*right_wall=((wall.row_look[x - 1] & (1 << y)) == (1 << y));
		}
		break;
	case 4:
		if (x >= 1) {
			*front_wall=((wall.row_look[x - 1] & (1 << y)) == (1 << y));
		}
		if (y >= 1) {
			*left_wall=((wall.column_look[y - 1] & (1 << x)) == (1 << x));
		}
		if (y <= 14) {
			*right_wall=((wall.column_look[y] & (1 << x)) == (1 << x));
		}
		break;
	}

}


void search_AroundWalkCount(unsigned short *front_count,unsigned short *right_count,unsigned short *back_count,unsigned short *left_count,int x,int y,int direction){
//int direction,int x_coordinate,int y_coordinate
	unsigned short north_count,east_count,south_count,west_count;
//	unsigned short front_count, right_count, back_count, left_count;

	if (y >= 15) {north_count = MAX_WALKCOUNT;}
	else {north_count = walk_count[x][y + 1];}

	if (x >= 15) {east_count = MAX_WALKCOUNT;}
	else {east_count = walk_count[x + 1][y];}

	if (y <= 0) {south_count = MAX_WALKCOUNT;}
	else {south_count = walk_count[x][y - 1];}

	if (x <= 0) {west_count = MAX_WALKCOUNT;}
	else {west_count = walk_count[x - 1][y];}


	switch (direction) {		//
	case 1:
		*front_count = north_count;
		*right_count = east_count;
		*back_count = south_count;
		*left_count = west_count;
		break;
	case 2:
		*front_count = east_count;
		*right_count = south_count;
		*back_count = west_count;
		*left_count = north_count;
		break;
	case 3:
		*front_count = south_count;
		*right_count = west_count;
		*back_count = north_count;
		*left_count = east_count;
		break;
	case 4:
		*front_count = west_count;
		*right_count = north_count;
		*back_count = east_count;
		*left_count = south_count;
		break;

	}


}





void search_AroundDijkstraCount(unsigned short *front_count,unsigned short *right_count,unsigned short *back_count,unsigned short *left_count,int x,int y,int direction){
//int direction,int x_coordinate,int y_coordinate
	unsigned short north_count,east_count,south_count,west_count;
//	unsigned short front_count, right_count, back_count, left_count;

	if (y >= 15) {north_count = 65535;}
	else {north_count = Dijkstra.column_count[x][y];}

	if (x >= 15) {east_count = 65535;}
	else {east_count = Dijkstra.row_count[y][x];}

	if (y <= 0) {south_count = 65535;}
	else {south_count = Dijkstra.column_count[x][y-1];}

	if (x <= 0) {west_count = 65535;}
	else {west_count = Dijkstra.row_count[y][x-1];}


	switch (direction) {		//
	case 1:
		*front_count = north_count;
		*right_count = east_count;
		*back_count = south_count;
		*left_count = west_count;
		break;
	case 2:
		*front_count = east_count;
		*right_count = south_count;
		*back_count = west_count;
		*left_count = north_count;
		break;
	case 3:
		*front_count = south_count;
		*right_count = west_count;
		*back_count = north_count;
		*left_count = east_count;
		break;
	case 4:
		*front_count = west_count;
		*right_count = north_count;
		*back_count = east_count;
		*left_count = south_count;
		break;

	}


}




void create_DijkstraMap(void){
	STACK_T stack_x;
	STACK_T stack_y;
	STACK_T stack_matrix;//行列
	STACK_T stack_direction;//向き(0北　1北東　2東　3南東　4南　5南西　6西　7北西　8エラー)
	STACK_T stack_cost;//引かれるコスト
	int16_t VerticalCost=VERTICALCOST;
	int16_t DiagonalCost=DIAGONALCOST;
	int16_t discount_v[V_NUM_MAX]={180,118,100,91,90};
	int16_t discount_d[D_NUM_MAX]={127,91,79,71,65,64};
	int16_t dis_cost_in;
	//printf("%d,%d,%d,%d,%d\n",discount_v[0],discount_v[1],discount_v[2],discount_v[3],discount_v[4]);
	//printf("%d,%d,%d,%d,%d,%d\n",discount_d[0],discount_d[1],discount_d[2],discount_d[3],discount_d[4],discount_d[5]);
	initStack_walk(&stack_x);
	initStack_walk(&stack_y);
	initStack_walk(&stack_matrix);
	initStack_walk(&stack_direction);
	initStack_walk(&stack_cost);
	for(int i=0;i<=15;i++){
		for(int j=0;j<=14;j++){
			Dijkstra.column_count[i][j]=65535;
			Dijkstra.row_count[i][j]=65535;
		}
	}
	Dijkstra.column_count[GOAL_X][GOAL_Y]=0;
	Dijkstra.column_count[GOAL_X+1][GOAL_Y]=0;
	Dijkstra.row_count[GOAL_Y][GOAL_X]=0;
	Dijkstra.row_count[GOAL_Y+1][GOAL_X]=0;
	pushStack_walk(&stack_x,GOAL_X);pushStack_walk(&stack_y,GOAL_Y);
	pushStack_walk(&stack_matrix,COLUMN);pushStack_walk(&stack_direction,8);pushStack_walk(&stack_cost,0);
	pushStack_walk(&stack_x,GOAL_X+1);pushStack_walk(&stack_y,GOAL_Y);
	pushStack_walk(&stack_matrix,COLUMN);pushStack_walk(&stack_direction,8);pushStack_walk(&stack_cost,0);
	pushStack_walk(&stack_x,GOAL_X);pushStack_walk(&stack_y,GOAL_Y);
	pushStack_walk(&stack_matrix,ROW);pushStack_walk(&stack_direction,8);pushStack_walk(&stack_cost,0);
	pushStack_walk(&stack_x,GOAL_X);pushStack_walk(&stack_y,GOAL_Y+1);
	pushStack_walk(&stack_matrix,ROW);pushStack_walk(&stack_direction,8);pushStack_walk(&stack_cost,0);



	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate,Row_or_Column,Direction,dis_cost;
	while (1) {

		Xcoordinate = popStack_walk(&stack_x);
		Ycoordinate = popStack_walk(&stack_y);
		Row_or_Column = popStack_walk(&stack_matrix);
		Direction = popStack_walk(&stack_direction);
		dis_cost = popStack_walk(&stack_cost);
		//printf("x %d,y %d,C(0)R(1) %d\n",Xcoordinate,Ycoordinate,Row_or_Column);
		//printf("cost_num %d\n",dis_cost);
		//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
		if (Xcoordinate == 65535 || Ycoordinate == 65535) {
			//printf("stack_end\n");
			break;
		}
		if(Row_or_Column==COLUMN){
			if(Ycoordinate <= 13){
				if(Direction==SLANT_NORTH){
					dis_cost_in=dis_cost+DISCOUNTCOST_V;
					if(dis_cost_in>=V_NUM_MAX){dis_cost_in=V_NUM_MAX-1;}
					VerticalCost=discount_v[dis_cost_in];
				}else{VerticalCost=discount_v[0];dis_cost_in=0;}
				if((wall.column[Ycoordinate+1] & (1 << Xcoordinate))==0 && Dijkstra.column_count[Xcoordinate][Ycoordinate+1]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+VerticalCost){
					Dijkstra.column_count[Xcoordinate][Ycoordinate+1]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+VerticalCost;
					pushStack_walk(&stack_x,Xcoordinate);
					pushStack_walk(&stack_y,Ycoordinate + 1);
					pushStack_walk(&stack_matrix,COLUMN);
					pushStack_walk(&stack_direction,SLANT_NORTH);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
			}
			if (Ycoordinate >= 1) {
				if(Direction==SLANT_SOUTH){
					dis_cost_in=dis_cost+DISCOUNTCOST_V;
					if(dis_cost_in>=V_NUM_MAX){dis_cost_in=V_NUM_MAX-1;}
					VerticalCost=discount_v[dis_cost_in];
				}else{VerticalCost=discount_v[0];dis_cost_in=0;}
				if((wall.column[Ycoordinate-1] & (1 << Xcoordinate))==0 && Dijkstra.column_count[Xcoordinate][Ycoordinate-1]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+VerticalCost){
					Dijkstra.column_count[Xcoordinate][Ycoordinate-1]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+VerticalCost;
					pushStack_walk(&stack_x,Xcoordinate);
					pushStack_walk(&stack_y,Ycoordinate - 1);
					pushStack_walk(&stack_matrix,COLUMN);
					pushStack_walk(&stack_direction,SLANT_SOUTH);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
			}
			if (Xcoordinate <= 14) {
				if(Direction==SLANT_SOUTH_EAST){
					dis_cost_in=dis_cost+DISCOUNTCOST_D;
					if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
					DiagonalCost=discount_d[dis_cost_in];
				}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
				if((wall.row[Xcoordinate] & (1 << Ycoordinate))==0 && Dijkstra.row_count[Ycoordinate][Xcoordinate]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost){
					Dijkstra.row_count[Ycoordinate][Xcoordinate]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost;
					pushStack_walk(&stack_x,Xcoordinate);
					pushStack_walk(&stack_y,Ycoordinate);
					pushStack_walk(&stack_matrix,ROW);
					pushStack_walk(&stack_direction,SLANT_SOUTH_EAST);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
				if(Direction==SLANT_NORTH_EAST){
					dis_cost_in=dis_cost+DISCOUNTCOST_D;
					if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
					DiagonalCost=discount_d[dis_cost_in];
				}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
				if((wall.row[Xcoordinate] & (1 << (Ycoordinate+1)))==0 && Dijkstra.row_count[Ycoordinate+1][Xcoordinate]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost){
					Dijkstra.row_count[Ycoordinate+1][Xcoordinate]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost;
					pushStack_walk(&stack_x,Xcoordinate);
					pushStack_walk(&stack_y,Ycoordinate+1);
					pushStack_walk(&stack_matrix,ROW);
					pushStack_walk(&stack_direction,SLANT_NORTH_EAST);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
			}
			if (Xcoordinate >= 1) {
				if(Direction==SLANT_SOUTH_WEST){
					dis_cost_in=dis_cost+DISCOUNTCOST_D;
					if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
					DiagonalCost=discount_d[dis_cost_in];
				}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
				if((wall.row[Xcoordinate-1] & (1 << Ycoordinate))==0 && Dijkstra.row_count[Ycoordinate][Xcoordinate-1]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost){
					Dijkstra.row_count[Ycoordinate][Xcoordinate-1]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost;
					pushStack_walk(&stack_x,Xcoordinate-1);
					pushStack_walk(&stack_y,Ycoordinate);
					pushStack_walk(&stack_matrix,ROW);
					pushStack_walk(&stack_direction,SLANT_SOUTH_WEST);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
				if(Direction==SLANT_NORTH_WEST){
					dis_cost_in=dis_cost+DISCOUNTCOST_D;
					if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
					DiagonalCost=discount_d[dis_cost_in];
				}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
				if((wall.row[Xcoordinate-1] & (1 << (Ycoordinate+1)))==0 && Dijkstra.row_count[Ycoordinate+1][Xcoordinate-1]>Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost){
					Dijkstra.row_count[Ycoordinate+1][Xcoordinate-1]=Dijkstra.column_count[Xcoordinate][Ycoordinate]+DiagonalCost;
					pushStack_walk(&stack_x,Xcoordinate-1);
					pushStack_walk(&stack_y,Ycoordinate+1);
					pushStack_walk(&stack_matrix,ROW);
					pushStack_walk(&stack_direction,SLANT_NORTH_WEST);
					pushStack_walk(&stack_cost,dis_cost_in);
				}
			}

		}
		if(Row_or_Column==ROW){
					if(Xcoordinate <= 13){
						if(Direction==SLANT_EAST){
							dis_cost_in=dis_cost+DISCOUNTCOST_V;
							if(dis_cost_in>=V_NUM_MAX){dis_cost_in=V_NUM_MAX-1;}
							VerticalCost=discount_v[dis_cost_in];
						}else{VerticalCost=discount_v[0];dis_cost_in=0;}
						if((wall.row[Xcoordinate+1] & (1 << Ycoordinate))==0 && Dijkstra.row_count[Ycoordinate][Xcoordinate+1]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+VerticalCost){
							Dijkstra.row_count[Ycoordinate][Xcoordinate+1]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+VerticalCost;
							pushStack_walk(&stack_x,Xcoordinate + 1);
							pushStack_walk(&stack_y,Ycoordinate);
							pushStack_walk(&stack_matrix,ROW);
							pushStack_walk(&stack_direction,SLANT_EAST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
					}
					if (Xcoordinate >= 1) {
						if(Direction==SLANT_WEST){
							dis_cost_in=dis_cost+DISCOUNTCOST_V;
							if(dis_cost_in>=V_NUM_MAX){dis_cost_in=V_NUM_MAX-1;}
							VerticalCost=discount_v[dis_cost_in];
						}else{VerticalCost=discount_v[0];dis_cost_in=0;}
						if((wall.row[Xcoordinate-1] & (1 << Ycoordinate))==0 && Dijkstra.row_count[Ycoordinate][Xcoordinate-1]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+VerticalCost){
							Dijkstra.row_count[Ycoordinate][Xcoordinate-1]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+VerticalCost;
							pushStack_walk(&stack_x,Xcoordinate - 1);
							pushStack_walk(&stack_y,Ycoordinate);
							pushStack_walk(&stack_matrix,ROW);
							pushStack_walk(&stack_direction,SLANT_WEST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
					}
					if (Ycoordinate <= 14) {
						if(Direction==SLANT_NORTH_WEST){
							dis_cost_in=dis_cost+DISCOUNTCOST_D;
							if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
							DiagonalCost=discount_d[dis_cost_in];
						}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
						if((wall.column[Ycoordinate] & (1 << Xcoordinate))==0 && Dijkstra.column_count[Xcoordinate][Ycoordinate]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost){
							Dijkstra.column_count[Xcoordinate][Ycoordinate]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost;
							pushStack_walk(&stack_x,Xcoordinate);
							pushStack_walk(&stack_y,Ycoordinate);
							pushStack_walk(&stack_matrix,COLUMN);
							pushStack_walk(&stack_direction,SLANT_NORTH_WEST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
						if(Direction==SLANT_NORTH_EAST){
							dis_cost_in=dis_cost+DISCOUNTCOST_D;
							if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
							DiagonalCost=discount_d[dis_cost_in];
						}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
						if((wall.column[Ycoordinate] & (1 << (Xcoordinate+1)))==0 && Dijkstra.column_count[Xcoordinate+1][Ycoordinate]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost){
							Dijkstra.column_count[Xcoordinate+1][Ycoordinate]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost;
							pushStack_walk(&stack_x,Xcoordinate + 1);
							pushStack_walk(&stack_y,Ycoordinate);
							pushStack_walk(&stack_matrix,COLUMN);
							pushStack_walk(&stack_direction,SLANT_NORTH_EAST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
					}
					if (Ycoordinate >= 1) {
						if(Direction==SLANT_SOUTH_WEST){
							dis_cost_in=dis_cost+DISCOUNTCOST_D;
							if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
							DiagonalCost=discount_d[dis_cost_in];
						}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
						if((wall.column[Ycoordinate-1] & (1 << Xcoordinate))==0 && Dijkstra.column_count[Xcoordinate][Ycoordinate-1]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost){
							Dijkstra.column_count[Xcoordinate][Ycoordinate-1]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost;
							pushStack_walk(&stack_x,Xcoordinate);
							pushStack_walk(&stack_y,Ycoordinate - 1);
							pushStack_walk(&stack_matrix,COLUMN);
							pushStack_walk(&stack_direction,SLANT_SOUTH_WEST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
						if(Direction==SLANT_SOUTH_EAST){
							dis_cost_in=dis_cost+DISCOUNTCOST_D;
							if(dis_cost_in>=D_NUM_MAX){dis_cost_in=D_NUM_MAX-1;}
							DiagonalCost=discount_d[dis_cost_in];
						}else{DiagonalCost=discount_d[0];dis_cost_in=0;}
						if((wall.column[Ycoordinate-1] & (1 << (Xcoordinate+1)))==0 && Dijkstra.column_count[Xcoordinate+1][Ycoordinate-1]>Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost){
							Dijkstra.column_count[Xcoordinate+1][Ycoordinate-1]=Dijkstra.row_count[Ycoordinate][Xcoordinate]+DiagonalCost;
							pushStack_walk(&stack_x,Xcoordinate+1);
							pushStack_walk(&stack_y,Ycoordinate-1);
							pushStack_walk(&stack_matrix,COLUMN);
							pushStack_walk(&stack_direction,SLANT_SOUTH_EAST);
							pushStack_walk(&stack_cost,dis_cost_in);
						}
					}

				}

		count_number+=1;

		}



}







void route_Dijkstra(void){
	STACK_T stack_x;
	STACK_T stack_y;
	STACK_T stack_matrix;//行列
	STACK_T stack_x_unknow;
	STACK_T stack_y_unknow;
	STACK_T stack_matrix_unknow;//行列
	initStack_walk(&stack_x);
	initStack_walk(&stack_y);
	initStack_walk(&stack_matrix);
	initStack_walk(&g_Goal_x);
	initStack_walk(&g_Goal_y);

	pushStack_walk(&stack_x,0);pushStack_walk(&stack_y,0);
	pushStack_walk(&stack_matrix,COLUMN);

	unsigned short front_count, right_count, back_count, left_count;

	_Bool front_wall;
	_Bool right_wall;
	_Bool left_wall;

	int x = 0;
	int y = 0;
	int direction = 1;


	while (1) {
//		if (mode_safty == 1) {break;}
		update_coordinate(&x,&y,direction);

		if((x == GOAL_X || x == GOAL_X+1) && (y == GOAL_Y || y == GOAL_Y+1)){
					break;
		}


		search_AroundDijkstraCount(&front_count,&right_count,&back_count,&left_count,x,y,direction);
		//get_wall(x,y,direction,&front_wall,&right_wall,&left_wall);
		//if (front_wall) {front_count = MAX_WALKCOUNT_DIJKSTRA;}
		//if (right_wall) {right_count = MAX_WALKCOUNT_DIJKSTRA;}
		//if (left_wall) {left_count = MAX_WALKCOUNT_DIJKSTRA;}

		if (front_count==MAX_WALKCOUNT_DIJKSTRA && right_count==MAX_WALKCOUNT_DIJKSTRA && left_count==MAX_WALKCOUNT_DIJKSTRA && back_count==MAX_WALKCOUNT_DIJKSTRA){
			// 迷路破損のため停止(一時停止後に周辺の地図情報を初期化して再探索に変更予定)

			break;
		}
		if (front_count <= right_count && front_count <= left_count && front_count <= back_count){
			// 直進
			switch (direction) {		//
			case 1:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			case 2:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			case 3:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y-1);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			case 4:
				pushStack_walk(&stack_x,x-1);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			}

		}

		if(right_count < front_count && right_count <= left_count && right_count <= back_count){
			// 右旋回
			switch (direction) {		//
			case 1:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			case 2:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y-1);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			case 3:
				pushStack_walk(&stack_x,x-1);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			case 4:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			}
			direction++;
		}
		if(left_count < front_count && left_count < right_count && left_count <= back_count){
			// 左旋回
			switch (direction) {		//
			case 1:
				pushStack_walk(&stack_x,x-1);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			case 2:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			case 3:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y);
				pushStack_walk(&stack_matrix,ROW);
				break;
			case 4:
				pushStack_walk(&stack_x,x);
				pushStack_walk(&stack_y,y-1);
				pushStack_walk(&stack_matrix,COLUMN);
				break;
			}
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

	unsigned short Xcoordinate,Ycoordinate,Row_or_Column;
	while (1) {

			Xcoordinate = popStack_walk(&stack_x);
			Ycoordinate = popStack_walk(&stack_y);
			Row_or_Column = popStack_walk(&stack_matrix);
			//printf("x %d,y %d,C(0)R(1) %d\n",Xcoordinate,Ycoordinate,Row_or_Column);
			//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
			if (Xcoordinate == 65535 || Ycoordinate == 65535) {
				//printf("stack_end\n");
				break;
			}
			if(Row_or_Column==COLUMN && ((wall.column_look[Ycoordinate] & (1 << Xcoordinate)) == 0)){
				//pushStack_walk(&stack_x_unknow,Xcoordinate);
				//pushStack_walk(&stack_y_unknow,Ycoordinate);
				//pushStack_walk(&stack_matrix_unknow,Row_or_Column);
				walk_count[Xcoordinate][Ycoordinate] = 0;
				walk_count[Xcoordinate][Ycoordinate + 1] = 0;
				pushStack_walk(&g_Goal_x,Xcoordinate);pushStack_walk(&g_Goal_y,Ycoordinate);
				pushStack_walk(&g_Goal_x,Xcoordinate);pushStack_walk(&g_Goal_y,Ycoordinate+1);
			}
			if(Row_or_Column==ROW && ((wall.row_look[Xcoordinate] & (1 << Ycoordinate)) == 0)){
				//pushStack_walk(&stack_x_unknow,Xcoordinate);
				//pushStack_walk(&stack_y_unknow,Ycoordinate);
				//pushStack_walk(&stack_matrix_unknow,Row_or_Column);
				walk_count[Xcoordinate][Ycoordinate] = 0;
				walk_count[Xcoordinate + 1][Ycoordinate] = 0;
				pushStack_walk(&g_Goal_x,Xcoordinate);pushStack_walk(&g_Goal_y,Ycoordinate);
				pushStack_walk(&g_Goal_x,Xcoordinate+1);pushStack_walk(&g_Goal_y,Ycoordinate);
			}
	}


}




void create_StepCountMap_unknown(void){
	//ここから歩数マップを作る．*************************************
	STACK_T stack_x;
	STACK_T stack_y;
	unsigned short goalX,goalY;
	for(uint8_t xx = 0;xx <= 15;xx++){
		for(uint8_t yy = 0;yy <= 15;yy++){
			walk_count[xx][yy] = 255;
		}
	}

	initStack_walk(&stack_x);
	initStack_walk(&stack_y);

	while (1) {

			goalX = popStack_walk(&g_Goal_x);
			goalY = popStack_walk(&g_Goal_y);
			//printf("x %d,y %d,C(0)R(1) %d\n",Xcoordinate,Ycoordinate,Row_or_Column);
			//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
			if (goalX == 65535 || goalY == 65535) {
				//printf("stack_end\n");
				break;
			}
			walk_count[goalX][goalY] = 0;
			pushStack_walk(&stack_x,goalX);pushStack_walk(&stack_y,goalY);
	}
	if(stack_x.tail == stack_x.head){
		walk_count[0][0] = 0;
		pushStack_walk(&stack_x,0);pushStack_walk(&stack_y,0);
		if (Dijkstra_maker_flag>=1){
			Dijkstra_maker_flag=2;
		}else{
			Dijkstra_maker_flag=1;
		}
	}else{
		Dijkstra_maker_flag=0;
	}
	//printf("(%d,%d),(%d,%d),(%d,%d),(%d,%d)\n",stack_x.data[0],stack_y.data[0],stack_x.data[1],stack_y.data[1],stack_x.data[2],stack_y.data[2],stack_x.data[3],stack_y.data[3]);
	//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north=1,wall_south=1,wall_east=1,wall_west=1;
	while (count_number <= 254) {

		Xcoordinate = popStack_walk(&stack_x);
		Ycoordinate = popStack_walk(&stack_y);
		//printf("x %d,y %d\n",Xcoordinate,Ycoordinate);
		//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
		if (Xcoordinate == 65535 || Ycoordinate == 65535) {
			//printf("stack_end\n");
			break;
		}

		if (Ycoordinate <= 14) {
			wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
		}
		if (Ycoordinate >= 1) {
			wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
		}
		if (Xcoordinate <= 14) {
			wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
		}
		if (Xcoordinate >= 1) {
			wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
		}

		if (walk_count[Xcoordinate][Ycoordinate + 1] == 255 && Ycoordinate != 15 && wall_north == 0) {
			walk_count[Xcoordinate][Ycoordinate + 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate + 1);
		}
		if (walk_count[Xcoordinate][Ycoordinate - 1] == 255 && Ycoordinate != 0 && wall_south == 0) {
			walk_count[Xcoordinate][Ycoordinate - 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate - 1);
		}
		if (walk_count[Xcoordinate + 1][Ycoordinate] == 255 && Xcoordinate != 15 && wall_east == 0) {
			walk_count[Xcoordinate + 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate + 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		if (walk_count[Xcoordinate - 1][Ycoordinate] == 255 && Xcoordinate != 0 && wall_west == 0) {
			walk_count[Xcoordinate - 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate - 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		count_number=walk_count[Xcoordinate][Ycoordinate] + 1;

		}

}






void create_StepCountMap_queue(void){
	//ここから歩数マップを作る．*************************************
	STACK_T stack_x;
	STACK_T stack_y;
	for(uint8_t xx = 0;xx <= 15;xx++){
		for(uint8_t yy = 0;yy <= 15;yy++){
			walk_count[xx][yy] = 255;
		}
	}
	initStack_walk(&stack_x);
	initStack_walk(&stack_y);


	walk_count[GOAL_X][GOAL_Y] = 0;
	walk_count[GOAL_X + 1][GOAL_Y] = 0;
	walk_count[GOAL_X][GOAL_Y + 1] = 0;
	walk_count[GOAL_X + 1][GOAL_Y + 1] = 0;
	pushStack_walk(&stack_x,GOAL_X);pushStack_walk(&stack_y,GOAL_Y);
	pushStack_walk(&stack_x,GOAL_X + 1);pushStack_walk(&stack_y,GOAL_Y);
	pushStack_walk(&stack_x,GOAL_X);pushStack_walk(&stack_y,GOAL_Y + 1);
	pushStack_walk(&stack_x,GOAL_X + 1);pushStack_walk(&stack_y,GOAL_Y + 1);
	//printf("(%d,%d),(%d,%d),(%d,%d),(%d,%d)\n",stack_x.data[0],stack_y.data[0],stack_x.data[1],stack_y.data[1],stack_x.data[2],stack_y.data[2],stack_x.data[3],stack_y.data[3]);
	//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north=1,wall_south=1,wall_east=1,wall_west=1;
	while (count_number <= 254) {

		Xcoordinate = popStack_walk(&stack_x);
		Ycoordinate = popStack_walk(&stack_y);
		//printf("x %d,y %d\n",Xcoordinate,Ycoordinate);
		//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
		if (Xcoordinate == 65535 || Ycoordinate == 65535) {
			//printf("stack_end\n");
			break;
		}

		if (Ycoordinate <= 14) {
			wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
		}
		if (Ycoordinate >= 1) {
			wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
		}
		if (Xcoordinate <= 14) {
			wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
		}
		if (Xcoordinate >= 1) {
			wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
		}

		if (walk_count[Xcoordinate][Ycoordinate + 1] == 255 && Ycoordinate != 15 && wall_north == 0) {
			walk_count[Xcoordinate][Ycoordinate + 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate + 1);
		}
		if (walk_count[Xcoordinate][Ycoordinate - 1] == 255 && Ycoordinate != 0 && wall_south == 0) {
			walk_count[Xcoordinate][Ycoordinate - 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate - 1);
		}
		if (walk_count[Xcoordinate + 1][Ycoordinate] == 255 && Xcoordinate != 15 && wall_east == 0) {
			walk_count[Xcoordinate + 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate + 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		if (walk_count[Xcoordinate - 1][Ycoordinate] == 255 && Xcoordinate != 0 && wall_west == 0) {
			walk_count[Xcoordinate - 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate - 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		count_number=walk_count[Xcoordinate][Ycoordinate] + 1;

		}

}



void create_StepCountMapBack_queue(void){
	//ここから歩数マップを作る．*************************************
	STACK_T stack_x;
	STACK_T stack_y;
	for(uint8_t xx = 0;xx <= 15;xx++){
		for(uint8_t yy = 0;yy <= 15;yy++){
			walk_count[xx][yy] = 255;
		}
	}
	initStack_walk(&stack_x);
	initStack_walk(&stack_y);


	walk_count[0][0] = 0;
	pushStack_walk(&stack_x,0);pushStack_walk(&stack_y,0);
	//printf("(%d,%d),(%d,%d),(%d,%d),(%d,%d)\n",stack_x.data[0],stack_y.data[0],stack_x.data[1],stack_y.data[1],stack_x.data[2],stack_y.data[2],stack_x.data[3],stack_y.data[3]);
	//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
	unsigned short coordinate;
	unsigned short count_number = 1;
	unsigned short Xcoordinate,Ycoordinate;
	unsigned short wall_north=1,wall_south=1,wall_east=1,wall_west=1;
	while (count_number <= 254) {

		Xcoordinate = popStack_walk(&stack_x);
		Ycoordinate = popStack_walk(&stack_y);
		//printf("x %d,y %d\n",Xcoordinate,Ycoordinate);
		//printf("x head %d tail %d\n y head %d tail %d\n",stack_x.head,stack_x.tail,stack_y.head,stack_y.tail);
		if (Xcoordinate == 65535 || Ycoordinate == 65535) {
			//printf("stack_end\n");
			break;
		}

		coordinate = (Xcoordinate * 16) + Ycoordinate;
		if (Ycoordinate <= 14) {
			wall_north = wall.column[Ycoordinate] & (1 << Xcoordinate);
		}
		if (Ycoordinate >= 1) {
			wall_south = wall.column[Ycoordinate - 1] & (1 << Xcoordinate);
		}
		if (Xcoordinate <= 14) {
			wall_east = wall.row[Xcoordinate] & (1 << Ycoordinate);
		}
		if (Xcoordinate >= 1) {
			wall_west = wall.row[Xcoordinate - 1] & (1 << Ycoordinate);
		}

		if (walk_count[Xcoordinate][Ycoordinate + 1] == 255 && Ycoordinate != 15 && wall_north == 0) {
			walk_count[Xcoordinate][Ycoordinate + 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate + 1);
		}
		if (walk_count[Xcoordinate][Ycoordinate - 1] == 255 && Ycoordinate != 0 && wall_south == 0) {
			walk_count[Xcoordinate][Ycoordinate - 1] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate);
			pushStack_walk(&stack_y,Ycoordinate - 1);
		}
		if (walk_count[Xcoordinate + 1][Ycoordinate] == 255 && Xcoordinate != 15 && wall_east == 0) {
			walk_count[Xcoordinate + 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate + 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		if (walk_count[Xcoordinate - 1][Ycoordinate] == 255 && Xcoordinate != 0 && wall_west == 0) {
			walk_count[Xcoordinate - 1][Ycoordinate] = walk_count[Xcoordinate][Ycoordinate] + 1;
			pushStack_walk(&stack_x,Xcoordinate - 1);
			pushStack_walk(&stack_y,Ycoordinate);
		}
		count_number=walk_count[Xcoordinate][Ycoordinate] + 1;

		}

}




void initStack_walk(STACK_T *stack){
//	for(int i=0;i<=MAX_QUEUE_NUM-1;i++){
//		stack->data[i] = 0;
//	}
    /* スタックを空に設定 */
	stack->head = 0;
    stack->tail = 0;
}



void pushStack_walk(STACK_T *stack, unsigned short input){

    /* データをデータの最後尾の１つ後ろに格納 */
    stack->data[stack->tail] = input;

    /* データの最後尾を１つ後ろに移動 */
    stack->tail = stack->tail + 1;

    /* 巡回シフト */
    if(stack->tail == MAX_QUEUE_NUM) stack->tail = 0;

    /* スタックが満杯なら何もせず関数終了 */
    if(stack->tail == stack->head ){
    	printf("stack_full\n");
        return;
    }
}


unsigned short popStack_walk(STACK_T *stack){
    unsigned short ret = 0;

    /* スタックが空なら何もせずに関数終了 */
    if(stack->tail == stack->head){
    	//printf("stack_empty\n");
        return 65535;
    }

    /* データの最前列からデータを取得 */
    ret = stack->data[stack->head];

    /* データの最前列を１つ前にずらす */
    stack->head = stack->head + 1;

    /* 巡回シフト */
    if(stack->head == MAX_QUEUE_NUM) stack->head = 0;

    /* 取得したデータを返却 */
    return ret;
}

















void maze_maker(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {}
void maze_maker2(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {}
void maze_makerhosuu(int direction, int x, int y) {}

void maze_makerRun(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {}

void maze_makeronly(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {}

void maze_makerback(int direction, int front_SEN, int left_SEN, int right_SEN,
		int x, int y) {}


void maze_display(void) {

	int tt = 14;
	int ss = 0;

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	for (tt = 14;tt >= -1;tt--){

		printf("|%5d", walk_count[0][tt + 1]);
		for(ss = 0;ss < 15;ss++){
			if ((wall.row[ss] & (1 << (tt + 1))) == (1 << (tt + 1))){
				printf("|%5d", walk_count[ss + 1][tt + 1]);
			}else{
				printf(" %5d", walk_count[ss + 1][tt + 1]);
			}
		}
		printf("|\n");
		if (tt <= -1) {
			break;
		}
		for(ss = 0;ss <= 15;ss++){
			if ((wall.column[tt] & (1 << ss)) == (1 << ss)){
				printf("+-----");
			}else{
				printf("+     ");
			}
		}

		printf("+\n");

	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");


	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");

	for (tt = 14;tt >= -1;tt--){
		printf("|%5d", walk_count[0][tt + 1]);
		for(ss = 0;ss < 15;ss++){
			if ((wall.row_look[ss] & (1 << (tt + 1))) == (1 << (tt + 1))){
				printf("|%5d", walk_count[ss + 1][tt + 1]);
			}else{
				printf(" %5d", walk_count[ss + 1][tt + 1]);
			}
		}
		printf("|\n");
		if (tt <= -1) {
			break;
		}
		for(ss = 0;ss <= 15;ss++){
			if ((wall.column_look[tt] & (1 << ss)) == (1 << ss)){
				printf("+-----");
			}else{
				printf("+     ");
			}
		}
		printf("+\n");
	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");

}






void maze_display_Dijkstra(void) {

	int tt = 14;
	int ss = 0;

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	for (tt = 14;tt >= -1;tt--){

		printf("|   ");//walk_count[tt + 1]
		for(ss = 0;ss < 15;ss++){
			if ((wall.row[ss] & (1 << (tt + 1))) == (1 << (tt + 1))){
				printf("  |   ");
			}else{
				printf("%5d ", Dijkstra.row_count[(tt + 1)][ss]);
			}
		}
		printf("   |\n");
		if (tt <= -1) {
			break;
		}
		for(ss = 0;ss <= 15;ss++){
			if ((wall.column[tt] & (1 << ss)) == (1 << ss)){
				printf("+-----");
			}else{
				printf("+%5d",Dijkstra.column_count[ss][tt]);
			}
		}

		printf("+\n");

	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");


	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n");
	for (tt = 14;tt >= -1;tt--){

		printf("|   ");//walk_count[tt + 1]
		for(ss = 0;ss < 15;ss++){

				printf("%5d ", Dijkstra.row_count[(tt + 1)][ss]);

		}
		printf("   |\n");
		if (tt <= -1) {
			break;
		}
		for(ss = 0;ss <= 15;ss++){
				printf("+%5d",Dijkstra.column_count[ss][tt]);
		}

		printf("+\n");

	}

	printf(
			"+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+\n\n");




}
