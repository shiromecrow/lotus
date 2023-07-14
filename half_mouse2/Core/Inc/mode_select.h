/*
 * mode_select.h
 *
 *  Created on: Jan 11, 2023
 *      Author: sf199
 */

#ifndef INC_MODE_SELECT_H_
#define INC_MODE_SELECT_H_

unsigned char mode_decision(unsigned char);

void mode_execution(unsigned char);

void mode_PLtest(unsigned char);

void mode_Running(unsigned char);

void mode_Tuning0(unsigned char);

void mode_WallSensorTuning(unsigned char);

void mode_WallSensorTuning_fast(unsigned char);

#endif /* INC_MODE_SELECT_H_ */
