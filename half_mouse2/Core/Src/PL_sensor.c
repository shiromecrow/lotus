/*
 * PL_sensor.c
 *
 *  Created on: Jan 10, 2023
 *      Author: sf199
 */


#include "PL_sensor.h"
#include "adc.h"
#include "dma.h"
#include "gpio.h"



uint16_t g_ADCBuffer[6];
char AD_step;


uint16_t g_sensor_on[5];
uint16_t g_sensor_off[5];

float g_V_batt;

/*******************************************************************/
/*	sensorのinit					(pl_sensor_init)	*/
/*******************************************************************/
/*	sensorを初期設定						*/
/*******************************************************************/
void pl_sensor_init(void){
	AD_step=0;
	//HAL_ADC_Init(&hadc1);
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
	//HAL_ADC_ConfigChannel(&hadc1,&sConfig);
}

/*******************************************************************/
/*	電圧の取得			(pl_getbatt)	*/
/*******************************************************************/
/*	戻り値に電圧を返す．						*/
/*******************************************************************/
float pl_getbatt(void){
	 float batt;
	 uint16_t battAD;


	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 50);
	battAD = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);
	batt = 3.3  * (float) battAD / 4095.0 * (100.0 + 50.0) / 50.0;
return batt;
}

/*******************************************************************/
/*	callback用関数			(pl_callback_getSensor)	*/
/*******************************************************************/
/*	DMAがスタートしたら実行するコード					*/
/*******************************************************************/
void pl_callback_getSensor(void) {
	uint16_t V_battAD;

	int j;
	HAL_ADC_Stop_DMA(&hadc1);


	switch (AD_step) {
	case 0:
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		j=0;
		while (j <= 1000) {j++;}
		break;
	case 1:
		g_sensor_on[0] = g_ADCBuffer[1];
		g_sensor_on[1] = g_ADCBuffer[2];

		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		j=0;
		while (j <= 1000) {j++;}
		break;
	case 2:
		g_sensor_on[2] = g_ADCBuffer[3];
		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin, GPIO_PIN_SET);
		j=0;
		while (j <= 1000) {j++;}
		break;
	case 3:
		g_sensor_on[3] = g_ADCBuffer[4];
		g_sensor_on[4] = g_ADCBuffer[5];


		HAL_GPIO_WritePin(SENSOR_LED1_GPIO_Port, SENSOR_LED1_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED2_GPIO_Port, SENSOR_LED2_Pin,
				GPIO_PIN_RESET);
		HAL_GPIO_WritePin(SENSOR_LED3_GPIO_Port, SENSOR_LED3_Pin,
				GPIO_PIN_RESET);
		j=0;
		while (j <= 50) {j++;}
		V_battAD = g_ADCBuffer[0];
		g_V_batt = 3.3 * (float) V_battAD / 4095.0 * (100.0 + 50.0) / 50.0;
		break;
	case 4:
		g_sensor_off[0] = g_ADCBuffer[1];
		g_sensor_off[1] = g_ADCBuffer[2];
		g_sensor_off[2] = g_ADCBuffer[3];
		g_sensor_off[3] = g_ADCBuffer[4];
		g_sensor_off[4] = g_ADCBuffer[5];

		break;
	}


	AD_step++;
	//for(j=0;j<=2000;j++){}
	if (AD_step != 4) {
		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer, sizeof(g_ADCBuffer) / sizeof(uint16_t));
	} else {
		AD_step = 0;

	}

	/* NOTE : This function Should not be modified, when the callback is needed,
	 the HAL_ADC_ConvCpltCallback could be implemented in the user file
	 */
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,sizeof(g_ADCBuffer)/sizeof(uint16_t));
	//HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer,
	//	sizeof(g_ADCBuffer) / sizeof(uint16_t));
}




/*******************************************************************/
/*	割り込み用動作関数(センサー取得)			(interupt_calSensor)	*/
/*******************************************************************/
/*	センサーの情報を取得する割り込み関数．						*/
/*******************************************************************/
void pl_interupt_getSensor(void){

		HAL_ADC_Start_DMA(&hadc1, g_ADCBuffer, sizeof(g_ADCBuffer) / sizeof(uint16_t));

}
