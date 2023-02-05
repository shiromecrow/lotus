/*
 * turning_parameter.c
 *
 *  Created on: 2023/01/31
 *      Author: sf199
 */


/*
 * parameter.c
 *
 *  Created on: 2019/11/18
 *      Author: sf199
 */
#include "turning_parameter.h"
#include "define.h"


parameter_speed speed300_exploration;

parameter_speed speed300_shortest;

parameter_speed speed800_shortest;

parameter_speed speed800_shortest_mollifier;

float get_center_velocity(parameter_speed Howspeed, int pass_number) {
	float End_velocity;
	if (pass_number == -2) {
		End_velocity = Howspeed.slalom_R.g_speed;
	} else if (pass_number == -3) {
		End_velocity = Howspeed.slalom_L.g_speed;
	} else if (pass_number == -4) {
		End_velocity = Howspeed.turn90_R.g_speed;
	} else if (pass_number == -5) {
		End_velocity = Howspeed.turn90_L.g_speed;
	} else if (pass_number == -6) {
		End_velocity = Howspeed.turn180_R.g_speed;
	} else if (pass_number == -7) {
		End_velocity = Howspeed.turn180_L.g_speed;
	} else if (pass_number == -8) {
		End_velocity = Howspeed.turn45in_R.g_speed;
	} else if (pass_number == -9) {
		End_velocity = Howspeed.turn45in_L.g_speed;
	} else if (pass_number == -10) {
		End_velocity = Howspeed.turn135in_R.g_speed;
	} else if (pass_number == -11) {
		End_velocity = Howspeed.turn135in_L.g_speed;
	} else if (pass_number == -12) {
		End_velocity = Howspeed.turn45out_R.g_speed;
	} else if (pass_number == -13) {
		End_velocity = Howspeed.turn45out_L.g_speed;
	} else if (pass_number == -14) {
		End_velocity = Howspeed.turn135out_R.g_speed;
	} else if (pass_number == -15) {
		End_velocity = Howspeed.turn135out_L.g_speed;
	} else if (pass_number == -16) {
		End_velocity = Howspeed.V90_R.g_speed;
	} else if (pass_number == -17) {
		End_velocity = Howspeed.V90_L.g_speed;
	} else {
		End_velocity = Howspeed.TurnCentervelocity;
	}

	return End_velocity;
}

void input_parameter(void) {

	speed300_exploration.SlalomCentervelocity = 300;
	speed300_exploration.TurnCentervelocity = 300;

	speed300_exploration.slalom_R.g_speed =
			speed300_exploration.SlalomCentervelocity;
	speed300_exploration.slalom_R.t_speed = 700; //550
	speed300_exploration.slalom_R.t_acc = 8000; //10000
	speed300_exploration.slalom_R.f_ofset = 7; //55;
	speed300_exploration.slalom_R.e_ofset = 20;

	speed300_exploration.slalom_L.g_speed =
			speed300_exploration.SlalomCentervelocity;
	speed300_exploration.slalom_L.t_speed = 700;
	speed300_exploration.slalom_L.t_acc = 8000;
	speed300_exploration.slalom_L.f_ofset = 1; //50;
	speed300_exploration.slalom_L.e_ofset = 19;

	speed300_shortest.SlalomCentervelocity =
			speed300_exploration.SlalomCentervelocity;
	speed300_shortest.TurnCentervelocity =
			speed300_exploration.TurnCentervelocity + 200;

	speed300_shortest.slalom_R.g_speed = speed300_exploration.slalom_R.g_speed;
	speed300_shortest.slalom_R.t_speed = speed300_exploration.slalom_R.t_speed;
	speed300_shortest.slalom_R.t_acc = speed300_exploration.slalom_R.t_acc;
	speed300_shortest.slalom_R.f_ofset = speed300_exploration.slalom_R.f_ofset
			+ MAZE_OFFSET; //55;
	speed300_shortest.slalom_R.e_ofset = speed300_exploration.slalom_R.e_ofset;

	speed300_shortest.slalom_L.g_speed = speed300_exploration.slalom_L.g_speed;
	speed300_shortest.slalom_L.t_speed = speed300_exploration.slalom_L.t_speed;
	speed300_shortest.slalom_L.t_acc = speed300_exploration.slalom_L.t_acc;
	speed300_shortest.slalom_L.f_ofset = speed300_exploration.slalom_L.f_ofset
			+ MAZE_OFFSET; //50;
	speed300_shortest.slalom_L.e_ofset = speed300_exploration.slalom_L.e_ofset;

	speed300_shortest.turn90_R.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn90_R.t_speed = 600;
	speed300_shortest.turn90_R.t_acc = 10000;
	speed300_shortest.turn90_R.f_ofset = 76;
	speed300_shortest.turn90_R.e_ofset = 107;

	speed300_shortest.turn90_L.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn90_L.t_speed = 600;
	speed300_shortest.turn90_L.t_acc = 10000;
	speed300_shortest.turn90_L.f_ofset = 77;
	speed300_shortest.turn90_L.e_ofset = 103;

	speed300_shortest.turn180_R.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn180_R.t_speed = 430;
	speed300_shortest.turn180_R.t_acc = 8000;
	speed300_shortest.turn180_R.f_ofset = 65;
	speed300_shortest.turn180_R.e_ofset = 80;

	speed300_shortest.turn180_L.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn180_L.t_speed = 450;
	speed300_shortest.turn180_L.t_acc = 8000;
	speed300_shortest.turn180_L.f_ofset = 60;
	speed300_shortest.turn180_L.e_ofset = 71;

	speed300_shortest.turn45in_R.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn45in_R.t_speed = 600;
	speed300_shortest.turn45in_R.t_acc = 10000;
	speed300_shortest.turn45in_R.f_ofset = 27;
	speed300_shortest.turn45in_R.e_ofset = 89;

	speed300_shortest.turn45in_L.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn45in_L.t_speed = 600;
	speed300_shortest.turn45in_L.t_acc = 10000;
	speed300_shortest.turn45in_L.f_ofset = 33;
	speed300_shortest.turn45in_L.e_ofset = 90;

	speed300_shortest.turn135in_R.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn135in_R.t_speed = 610;
	speed300_shortest.turn135in_R.t_acc = 8000;
	speed300_shortest.turn135in_R.f_ofset = 67;
	speed300_shortest.turn135in_R.e_ofset = 73;

	speed300_shortest.turn135in_L.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn135in_L.t_speed = 610;
	speed300_shortest.turn135in_L.t_acc = 8000;
	speed300_shortest.turn135in_L.f_ofset = 67;
	speed300_shortest.turn135in_L.e_ofset = 73;

	speed300_shortest.turn45out_R.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn45out_R.t_speed = 600;
	speed300_shortest.turn45out_R.t_acc = 10000;
	speed300_shortest.turn45out_R.f_ofset = 57;
	speed300_shortest.turn45out_R.e_ofset = 57;

	speed300_shortest.turn45out_L.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn45out_L.t_speed = 600;
	speed300_shortest.turn45out_L.t_acc = 10000;
	speed300_shortest.turn45out_L.f_ofset = 64;
	speed300_shortest.turn45out_L.e_ofset = 52;

	speed300_shortest.turn135out_R.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn135out_R.t_speed = 660;
	speed300_shortest.turn135out_R.t_acc = 8000;
	speed300_shortest.turn135out_R.f_ofset = 55;
	speed300_shortest.turn135out_R.e_ofset = 100;

	speed300_shortest.turn135out_L.g_speed =
			speed300_shortest.TurnCentervelocity;
	speed300_shortest.turn135out_L.t_speed = 660;
	speed300_shortest.turn135out_L.t_acc = 8000;
	speed300_shortest.turn135out_L.f_ofset = 55;
	speed300_shortest.turn135out_L.e_ofset = 103;

	speed300_shortest.V90_R.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.V90_R.t_speed = 700;
	speed300_shortest.V90_R.t_acc = 11000;
	speed300_shortest.V90_R.f_ofset = 35;
	speed300_shortest.V90_R.e_ofset = 56;

	speed300_shortest.V90_L.g_speed = speed300_shortest.TurnCentervelocity;
	speed300_shortest.V90_L.t_speed = 700;
	speed300_shortest.V90_L.t_acc = 11000;
	speed300_shortest.V90_L.f_ofset = 32;
	speed300_shortest.V90_L.e_ofset = 60;

//*********************************800********************************************

	speed800_shortest.SlalomCentervelocity = 500;
	speed800_shortest.TurnCentervelocity = 500;

	speed800_shortest.slalom_R.g_speed = 1000;
	speed800_shortest.slalom_R.t_speed = 1000;
	speed800_shortest.slalom_R.t_acc = 14000;
	speed800_shortest.slalom_R.f_ofset = 0;
	speed800_shortest.slalom_R.e_ofset = 15;

	speed800_shortest.slalom_L.g_speed = 1000;
	speed800_shortest.slalom_L.t_speed = 1000;
	speed800_shortest.slalom_L.t_acc = 14000;
	speed800_shortest.slalom_L.f_ofset = 5;
	speed800_shortest.slalom_L.e_ofset = 5;

	speed800_shortest.turn90_R.g_speed = 500;
	speed800_shortest.turn90_R.t_speed = 650;
	speed800_shortest.turn90_R.t_acc = 15000;
	speed800_shortest.turn90_R.f_ofset = 69;
	speed800_shortest.turn90_R.e_ofset = 52;

	speed800_shortest.turn90_L.g_speed = 500;
	speed800_shortest.turn90_L.t_speed = 650;
	speed800_shortest.turn90_L.t_acc = 15000;
	speed800_shortest.turn90_L.f_ofset = 79;
	speed800_shortest.turn90_L.e_ofset = 49;

	speed800_shortest.turn180_R.g_speed = 500;
	speed800_shortest.turn180_R.t_speed = 600;
	speed800_shortest.turn180_R.t_acc = 15000;
	speed800_shortest.turn180_R.f_ofset = 65;
	speed800_shortest.turn180_R.e_ofset = 50;

	speed800_shortest.turn180_L.g_speed = 500;
	speed800_shortest.turn180_L.t_speed = 600;
	speed800_shortest.turn180_L.t_acc = 15000;
	speed800_shortest.turn180_L.f_ofset = 60;
	speed800_shortest.turn180_L.e_ofset = 54;

	speed800_shortest.turn45in_R.g_speed = 500;
	speed800_shortest.turn45in_R.t_speed = 650;
	speed800_shortest.turn45in_R.t_acc = 15000;
	speed800_shortest.turn45in_R.f_ofset = 60;
	speed800_shortest.turn45in_R.e_ofset = 40;

	speed800_shortest.turn45in_L.g_speed = 500;
	speed800_shortest.turn45in_L.t_speed = 650;
	speed800_shortest.turn45in_L.t_acc = 15000;
	speed800_shortest.turn45in_L.f_ofset = 64;
	speed800_shortest.turn45in_L.e_ofset = 44;

	speed800_shortest.turn135in_R.g_speed = 500;
	speed800_shortest.turn135in_R.t_speed = 650;
	speed800_shortest.turn135in_R.t_acc = 15000;
	speed800_shortest.turn135in_R.f_ofset = 75;
	speed800_shortest.turn135in_R.e_ofset = 40;

	speed800_shortest.turn135in_L.g_speed = 500;
	speed800_shortest.turn135in_L.t_speed = 650;
	speed800_shortest.turn135in_L.t_acc = 15000;
	speed800_shortest.turn135in_L.f_ofset = 70;
	speed800_shortest.turn135in_L.e_ofset = 44;

	speed800_shortest.turn45out_R.g_speed = 500;
	speed800_shortest.turn45out_R.t_speed = 650;
	speed800_shortest.turn45out_R.t_acc = 15000;
	speed800_shortest.turn45out_R.f_ofset = 75;
	speed800_shortest.turn45out_R.e_ofset = 48;

	speed800_shortest.turn45out_L.g_speed = 500;
	speed800_shortest.turn45out_L.t_speed = 650;
	speed800_shortest.turn45out_L.t_acc = 15000;
	speed800_shortest.turn45out_L.f_ofset = 58;
	speed800_shortest.turn45out_L.e_ofset = 48;

	speed800_shortest.turn135out_R.g_speed = 500;
	speed800_shortest.turn135out_R.t_speed = 650;
	speed800_shortest.turn135out_R.t_acc = 15000;
	speed800_shortest.turn135out_R.f_ofset = 75;
	speed800_shortest.turn135out_R.e_ofset = 60;

	speed800_shortest.turn135out_L.g_speed = 500;
	speed800_shortest.turn135out_L.t_speed = 650;
	speed800_shortest.turn135out_L.t_acc = 15000;
	speed800_shortest.turn135out_L.f_ofset = 80;
	speed800_shortest.turn135out_L.e_ofset = 64;

	speed800_shortest.V90_R.g_speed = 500;
	speed800_shortest.V90_R.t_speed = 650;
	speed800_shortest.V90_R.t_acc = 15000;
	speed800_shortest.V90_R.f_ofset = 55;
	speed800_shortest.V90_R.e_ofset = 40;

	speed800_shortest.V90_L.g_speed = 500;
	speed800_shortest.V90_L.t_speed = 650;
	speed800_shortest.V90_L.t_acc = 15000;
	speed800_shortest.V90_L.f_ofset = 50;
	speed800_shortest.V90_L.e_ofset = 44;


	//********************************800********************************************
	speed800_shortest_mollifier.SlalomCentervelocity = 800;
	speed800_shortest_mollifier.TurnCentervelocity = 800;

	speed800_shortest_mollifier.slalom_R.g_speed =
			speed800_shortest_mollifier.SlalomCentervelocity;
	speed800_shortest_mollifier.slalom_R.t_speed = 1600;
	speed800_shortest_mollifier.slalom_R.t_acc = 60000;
	speed800_shortest_mollifier.slalom_R.f_ofset = 15;
	speed800_shortest_mollifier.slalom_R.e_ofset = 28;

	speed800_shortest_mollifier.slalom_L.g_speed =
			speed800_shortest_mollifier.SlalomCentervelocity;
	speed800_shortest_mollifier.slalom_L.t_speed = 800;
	speed800_shortest_mollifier.slalom_L.t_acc = 60000;
	speed800_shortest_mollifier.slalom_L.f_ofset = 15;
	speed800_shortest_mollifier.slalom_L.e_ofset = 32;

	speed800_shortest_mollifier.turn90_R.g_speed = 800;
	speed800_shortest_mollifier.turn90_R.t_speed = 1400;
	speed800_shortest_mollifier.turn90_R.t_acc = 31000;
	speed800_shortest_mollifier.turn90_R.f_ofset = 49;
	speed800_shortest_mollifier.turn90_R.e_ofset = 91;

	speed800_shortest_mollifier.turn90_L.g_speed = 800;
	speed800_shortest_mollifier.turn90_L.t_speed = 1400;
	speed800_shortest_mollifier.turn90_L.t_acc = 31000;
	speed800_shortest_mollifier.turn90_L.f_ofset = 49;
	speed800_shortest_mollifier.turn90_L.e_ofset = 95;

	speed800_shortest_mollifier.turn180_R.g_speed =800;
	speed800_shortest_mollifier.turn180_R.t_speed = 1320;
	speed800_shortest_mollifier.turn180_R.t_acc = 19000;
	speed800_shortest_mollifier.turn180_R.f_ofset = 7;
	speed800_shortest_mollifier.turn180_R.e_ofset = 95;

	speed800_shortest_mollifier.turn180_L.g_speed = 800;
	speed800_shortest_mollifier.turn180_L.t_speed = 1320;
	speed800_shortest_mollifier.turn180_L.t_acc = 19000;
	speed800_shortest_mollifier.turn180_L.f_ofset = 7;
	speed800_shortest_mollifier.turn180_L.e_ofset = 93;

	speed800_shortest_mollifier.turn45in_R.g_speed = 800;
	speed800_shortest_mollifier.turn45in_R.t_speed = 1130;
	speed800_shortest_mollifier.turn45in_R.t_acc = 66000;
	speed800_shortest_mollifier.turn45in_R.f_ofset = 13;
	speed800_shortest_mollifier.turn45in_R.e_ofset = 78;

	speed800_shortest_mollifier.turn45in_L.g_speed = 800;
	speed800_shortest_mollifier.turn45in_L.t_speed = 1130;
	speed800_shortest_mollifier.turn45in_L.t_acc = 67000;
	speed800_shortest_mollifier.turn45in_L.f_ofset = 11;
	speed800_shortest_mollifier.turn45in_L.e_ofset = 76;

	speed800_shortest_mollifier.turn135in_R.g_speed = 800;
	speed800_shortest_mollifier.turn135in_R.t_speed = 1470;
	speed800_shortest_mollifier.turn135in_R.t_acc = 34000;
	speed800_shortest_mollifier.turn135in_R.f_ofset = 8;
	speed800_shortest_mollifier.turn135in_R.e_ofset = 106;

	speed800_shortest_mollifier.turn135in_L.g_speed = 800;
	speed800_shortest_mollifier.turn135in_L.t_speed = 1470;
	speed800_shortest_mollifier.turn135in_L.t_acc = 34000;
	speed800_shortest_mollifier.turn135in_L.f_ofset = 8;
	speed800_shortest_mollifier.turn135in_L.e_ofset = 101;

	speed800_shortest_mollifier.turn45out_R.g_speed = 800;
	speed800_shortest_mollifier.turn45out_R.t_speed = 1120;
	speed800_shortest_mollifier.turn45out_R.t_acc = 42000;
	speed800_shortest_mollifier.turn45out_R.f_ofset = 43;
	speed800_shortest_mollifier.turn45out_R.e_ofset = 58;

	speed800_shortest_mollifier.turn45out_L.g_speed = 800;
	speed800_shortest_mollifier.turn45out_L.t_speed = 1120;
	speed800_shortest_mollifier.turn45out_L.t_acc = 42000;
	speed800_shortest_mollifier.turn45out_L.f_ofset = 46;
	speed800_shortest_mollifier.turn45out_L.e_ofset = 81;

	speed800_shortest_mollifier.turn135out_R.g_speed = 800;
	speed800_shortest_mollifier.turn135out_R.t_speed = 1550;
	speed800_shortest_mollifier.turn135out_R.t_acc = 34000;
	speed800_shortest_mollifier.turn135out_R.f_ofset = 15;
	speed800_shortest_mollifier.turn135out_R.e_ofset = 118;

	speed800_shortest_mollifier.turn135out_L.g_speed = 800;
	speed800_shortest_mollifier.turn135out_L.t_speed = 1550;
	speed800_shortest_mollifier.turn135out_L.t_acc = 34000;
	speed800_shortest_mollifier.turn135out_L.f_ofset = 15;
	speed800_shortest_mollifier.turn135out_L.e_ofset = 116;

	speed800_shortest_mollifier.V90_R.g_speed = 800;
	speed800_shortest_mollifier.V90_R.t_speed = 1640;
	speed800_shortest_mollifier.V90_R.t_acc = 33000;
	speed800_shortest_mollifier.V90_R.f_ofset = 20;
	speed800_shortest_mollifier.V90_R.e_ofset = 72;

	speed800_shortest_mollifier.V90_L.g_speed = 800;
	speed800_shortest_mollifier.V90_L.t_speed = 1640;
	speed800_shortest_mollifier.V90_L.t_acc = 33000;
	speed800_shortest_mollifier.V90_L.f_ofset = 20;
	speed800_shortest_mollifier.V90_L.e_ofset = 72;



}