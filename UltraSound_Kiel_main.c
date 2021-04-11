/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include  "hcSR04.h"
#include "stdio.h"
#include <stdlib.h>
#include <stdint.h>
#define MAX 1000
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
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
uint8_t temp1[2];
int arrayCounter=0;
uint8_t decision=1;
	uint8_t out[] = {0,0,'.',0,0,'\r','\n'};
	uint8_t temp22;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
typedef void(*funcptr)();
void QueTask(funcptr ,int );
void ReRunMe(int);
void swap (int , int );
void sort ();
void sort2 ();
void QueTaskDelay(funcptr ,int );
void Dispatch();
void Init();
int doneflag = 0;
int c=0;
int frequency = 0;
struct tasks{
    funcptr funcName;
    int priority;
    int delay;
};

struct taskQueue{
    struct tasks currentTask[10];
    int current_size;
    int max_size;
};


struct taskQueue newQueue;
struct taskQueue delayQueue;
void QueTask(funcptr function_name,int priority2)
{
    newQueue.currentTask[newQueue.current_size].funcName=function_name;
    newQueue.currentTask[newQueue.current_size].priority=priority2;
    newQueue.current_size++;
    sort();
}
void QueTaskDelay(funcptr function_name,int ticks)
{
	//enque function in delay queue
    delayQueue.currentTask[delayQueue.current_size].funcName = function_name;
    delayQueue.currentTask[delayQueue.current_size].delay = ticks;
    delayQueue.currentTask[delayQueue.current_size].priority=newQueue.currentTask[0].priority;
    delayQueue.current_size = delayQueue.current_size + 1;
    sort2();


}
void ReRunMe(int ticks)
{
	if (ticks==0)
	{
		//add task to ready queue
        QueTask(newQueue.currentTask[0].funcName,newQueue.currentTask[0].priority);

 	}
	else
	{
		//add task into DelayQueue, priority based on number passed (ticks)
        QueTaskDelay(newQueue.currentTask[0].funcName,ticks);
	}
}
void Dispatch()
{
    int j=0;
    while(delayQueue.currentTask[0].delay==0)
    {
            QueTask(delayQueue.currentTask[0].funcName,delayQueue.currentTask[0].priority);
						int i =1;
            for(i;i<delayQueue.current_size;i++)
            {
                delayQueue.currentTask[i-1]=delayQueue.currentTask[i];
            }
            delayQueue.currentTask[delayQueue.current_size-1].funcName = NULL;
            delayQueue.currentTask[delayQueue.current_size-1].delay = MAX;
            delayQueue.currentTask[delayQueue.current_size-1].priority = -1;
            delayQueue.current_size--;
    }
	//	int j=0;
//	for (j;j<delayQueue.current_size;j++) 
//		if (delayQueue.currentTask[j].delay!=0)
//			delayQueue.currentTask[j].delay--;
    if (newQueue.current_size!=0){
    newQueue.currentTask[0].funcName(); 
		int i =1;
    for(i;i<newQueue.current_size;i++)
    {
        newQueue.currentTask[i-1]=newQueue.currentTask[i];      
    }
    newQueue.currentTask[newQueue.current_size-1].funcName = NULL;
    newQueue.currentTask[newQueue.current_size-1].priority = 0;
    newQueue.current_size--;
    }
    if ((delayQueue.current_size==0)&&(newQueue.current_size==0)) doneflag=1;
}


void swap (int x, int y)
{
    struct tasks temp =newQueue.currentTask[x];
    newQueue.currentTask[x] = newQueue.currentTask[y];
    newQueue.currentTask[y] = temp;
}

void swap2 (int x, int y)
{
    struct tasks temp =delayQueue.currentTask[x];
    delayQueue.currentTask[x] = delayQueue.currentTask[y];
    delayQueue.currentTask[y] = temp;

}
void sort ()
{
		int i = 0;
		int j = 0;
    for (i; i<newQueue.current_size;i++)
    {
			j = i;
        for(j; j<newQueue.current_size;j++)
        {
            if (newQueue.currentTask[i].priority>newQueue.currentTask[j].priority) 
            {
                swap (i,j);
            }
        }
    }
}
void sort2()
{
	int i = 0;
	int j = 0;
   for (i; i<delayQueue.current_size;i++)
    {
			j=i;
        for(j; j<delayQueue.current_size;j++)
        {
            if (delayQueue.currentTask[i].delay>delayQueue.currentTask[j].delay) 
            {
                swap2 (i,j);
            }
        }
    } 
}
void Init()
{
	newQueue.current_size=0;
    delayQueue.current_size=0;
		int i = 0;
    for (i; i<10;i++) delayQueue.currentTask[i].delay=MAX;
} 
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t hexToAscii(uint8_t n)//4-bit hex value converted to an ascii character
{
 if (n>=0 && n<=9) n = n + '0';
 else n = n - 10 + 'A';
 return n;
}
void ReadDistance()
{
	HCSR04_Read();
	HAL_Delay(200);
	ReRunMe(10);
}
void toggleBuzzer()
{
//	int x = temp22 - '0';
//	if(temp22>9)
//	{
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
//	}
//	else{
//		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
//	}
//	
	int x = 0;
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
	for(x;x<frequency;x++);
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
	for(x;x<frequency;x++);
	ReRunMe(1);
}

void setfrequency()
{
	if (temp22>9) frequency = 0;
	else if (temp22>8) frequency =10000*30;
	else if (temp22>6) frequency =10000*20;
	else if (temp22>4) frequency =10000*10;
	else if (temp22>2) frequency = 10000*1;
	//else frequency = 5;
	ReRunMe(10);
}

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

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_IC_Start_IT(&htim1,TIM_CHANNEL_1);
  /* USER CODE END 2 */
	Init();
	QueTask(&ReadDistance,0);
	QueTask(&setfrequency,1);
	QueTask(&toggleBuzzer,2);
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		Dispatch();
		
		//HCSR04_Read();
	  //HAL_Delay(200);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim1, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA4 PA9 */
  GPIO_InitStruct.Pin = GPIO_PIN_4|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
