/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "PL_LED.h"
#include "PL_timer.h"
#include "PL_gyro.h"
#include "PL_encoder.h"
#include "PL_sensor.h"
#include "PL_flash.h"
#include "PL_motor.h"
#include "CL_gyro.h"
#include "CL_encoder.h"
#include "CL_sensor.h"
#include "PID_EncoderGyro.h"
#include "PID_wall.h"
#include "Control_motor.h"
#include "record.h"
#include "mode_select.h"
#include "turning_parameter.h"
#include "fail_safe.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
	uint16_t mode2;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  MX_DMA_Init();
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_TIM6_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_DMA_Init();
  MX_SPI3_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
  pl_timer_init();
  pl_gyro_init();
  pl_sensor_init();
  reset_distance();
  reset_gyro();
  reset_speed();
  record_reset();
  pl_motor_init();
  PID_Init();
  init_WallControl();
  Control_mode_Init();
  init_FailSafe();
  input_parameter();

	//uint8_t hello[] = "Hello World\n\r";
  //float PI=3.14;
  //uint8_t hoge = 3;
  int mode=0;
	printf("ON_SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_sensor_on[0],
							g_sensor_on[1], g_sensor_on[2], g_sensor_on[3], g_sensor_on[4]);
	printf("OFF_SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_sensor_off[0],
							g_sensor_off[1], g_sensor_off[2], g_sensor_off[3], g_sensor_off[4]);
	battcheak();

//起動cheak
	int yellow_count=1;
	for(int i=0;i<8;i++){
		pl_yellow_LED_count(yellow_count);
		HAL_Delay(50);
		yellow_count=yellow_count*2;
	}
	for(int i=0;i<9;i++){
			pl_yellow_LED_count(yellow_count);
			HAL_Delay(50);
			yellow_count=yellow_count/2;
	}
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  		mode=mode_decision(mode);
//	  		clear_Ierror();
	  		reset_distance();
	  		reset_gyro();
	  		reset_speed();

	  		mode_execution(mode);

	  		error_mode = 0;

	  		// test USART
	  	//HAL_UART_Transmit(&huart1, hello, sizeof(hello), 1000);
	  	//printf("hello=%s", hello);
	  	//printf("hoge=%d\n\r", hoge);
	  	//printf("M_PI=%f\n\r", PI);
	  	// test GYRO
//	  	ICM20602_DataUpdate();
//	  	printf("gyro x : %5.5f, y : %5.5f,z : %5.5f, accel x : %5.5f, y :%5.5f, z : %5.5f\r",
//	  			gyro.omega_x, gyro.omega_y, gyro.omega_z, gyro.accel_x,gyro.accel_y, gyro.accel_z);
	  	// test ENCODER
	  	//AS5047_DataUpdate();
	  	//printf("encoderR : %5.5f, encoderL : %5.5f\r", encoder_R,encoder_L);

	  	//printf("E_distance_R : %5.5f, E_distance_L : %5.5f\r", E_distanceR,E_distanceL);
		//sensor
//	  	for(int i=0; i<6; i++){
//	  	        HAL_ADC_Start(&hadc1);
//	  	        HAL_ADC_PollForConversion(&hadc1, 100);
//	  	      g_ADCBuffer[i] = HAL_ADC_GetValue(&hadc1);
//	  	    }
	  	//HAL_ADC_Stop(&hadc1);
//		  HAL_ADC_Stop_DMA(&hadc1);
//	  	if (HAL_ADC_Start_DMA(&hadc1, (uint32_t*)(g_ADCBuffer),6) != HAL_OK)
//		  {
//		    Error_Handler();
//		  }

//		printf("BATT=%d,SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_ADCBuffer[0],
//				g_ADCBuffer[1], g_ADCBuffer[2], g_ADCBuffer[3], g_ADCBuffer[4], g_ADCBuffer[5]);

//		printf("ON_SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_sensor_on[0],
//								g_sensor_on[1], g_sensor_on[2], g_sensor_on[3], g_sensor_on[4]);
//		printf("OFF_SEN1=%d,SEN2=%d,SEN3=%d,SEN4=%d,SEN5=%d\n", g_sensor_off[0],
//								g_sensor_off[1], g_sensor_off[2], g_sensor_off[3], g_sensor_off[4]);
//		if(g_sensor_on[0]>800 && g_sensor_on[2]>800 && g_sensor_on[4]>800){
//					HAL_GPIO_WritePin(MOTOR_L_CWCCW_GPIO_Port,MOTOR_L_CWCCW_Pin,GPIO_PIN_RESET);
//					HAL_GPIO_WritePin(MOTOR_R_CWCCW_GPIO_Port,MOTOR_R_CWCCW_Pin,GPIO_PIN_SET);
//					HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
//					HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//					wait_ms(2000);
//					HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
//					HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);
//		}
//		wait_ms(10000);
		//HAL_TIM_PWM_Start(&htim16, TIM_CHANNEL_1);
//		HAL_GPIO_WritePin(MOTOR_L_CWCCW_GPIO_Port,MOTOR_L_CWCCW_Pin,GPIO_PIN_SET);
//		HAL_GPIO_WritePin(MOTOR_R_CWCCW_GPIO_Port,MOTOR_R_CWCCW_Pin,GPIO_PIN_SET);
//		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
//		wait_ms(6000);
//		HAL_TIM_PWM_Stop(&htim16, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
//		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3);



  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV4;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
