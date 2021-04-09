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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAX 1000
//#include "ds3231.h"
//#include "rtc_ds3231.h"
//#include <LiquidCrystal.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t temp1[2];
int arrayCounter=0;
uint8_t decision=1;
	uint8_t out[] = {0,0,'.',0,0,'\r','\n'};
	uint8_t firsttemp[2];
	uint8_t secondtemp[2];
	int temp=0;
		uint8_t temp5;
	int flagToggle=0;
	int flagCheck = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
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
	//uint8_t tt = ticks + '0';
	//HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
	if (ticks==0)
	{
		//add task to ready queue
			//HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
        QueTask(newQueue.currentTask[0].funcName,newQueue.currentTask[0].priority);

 	}
	else
	{
		//add task into DelayQueue, priority based on number passed (ticks)
			//HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
        QueTaskDelay(newQueue.currentTask[0].funcName,ticks);
	}
}
void Dispatch()
{
    int j=0;
	uint8_t tt;
    while(delayQueue.currentTask[0].delay==0)
    {
						//tt = delayQueue.currentTask[0].delay + '0';
						//HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
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
    if (newQueue.current_size!=0){
    newQueue.currentTask[0].funcName(); //feeh hga hena
			tt = newQueue.currentTask[0].priority + '0';
			HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
		//tt = newQueue.current_size + '0';
		//HAL_UART_Transmit(&huart1,&tt, sizeof(tt), 100);
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

/* USER CODE BEGIN PFP */


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t hexToAscii(uint8_t n)//4-bit hex value converted to an ascii character
{
 if (n>=0 && n<=9) n = n + '0';
 else n = n - 10 + 'A';
 return n;
}
/* USER CODE END 0 */

/*
  * @brief  The application entry point.
  * @retval int
  */
void toggleLED()
{
	HAL_UART_Transmit(&huart1,"Toggle",sizeof("Toggle"),200);
	if (flagToggle==1)
		{
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
				HAL_Delay(300);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
				HAL_Delay(300);

				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET);
				HAL_Delay(300);
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
				HAL_Delay(300);
			
		}
	ReRunMe(6);
}
void CheckThreshold()
{
		HAL_UART_Transmit(&huart1,"Threshold",sizeof("Threshold"),200);

	if (flagCheck==1)
	{
	
	temp = ((temp1[0]-'0')*10) + (temp1[1]-'0');
	int x = ((out[0]-'0')*10) + (out[1]-'0');
		if (x >= temp) 
		//QueTask(&toggleLED,0);
		flagToggle=1;
	else 
		flagToggle=0;
	}
		//toggleLED();
	flagCheck=0;
	ReRunMe(5);
}
void ReadTemp()
{
	 //send seconds register address 00h to read from
 HAL_I2C_Master_Transmit(&hi2c1, 0xD0, firsttemp, 1, 10);
 //read data of register 00h to firsttemp[1]
 HAL_I2C_Master_Receive(&hi2c1, 0xD1, firsttemp+1, 1, 10);
	 
	 HAL_I2C_Master_Transmit(&hi2c1, 0xD0, secondtemp, 1, 10);
 //read data of register 00h to firsttemp[1]
 HAL_I2C_Master_Receive(&hi2c1, 0xD1, secondtemp+1, 1, 10);
 //prepare UART output
// out[1] = hexToAscii(firsttemp[1] >> 4 );
// out[0] = hexToAscii(firsttemp[1] & 0x11 );
	//CheckThreshold();
	//QueTask(&CheckThreshold,1);
	out[1] = firsttemp[1] %10 +'0';
	firsttemp[1] = firsttemp[1]/10;
	out[0] = firsttemp[1] %10 +'0';
	firsttemp[1] = firsttemp[1]/10;
	 
	out[4] = secondtemp[1] %10 +'0';
	secondtemp[1] = secondtemp[1]/10;
	out[3] = secondtemp[1] %10 +'0';
	secondtemp[1] = secondtemp[1]/10;

 // transmit time to UART
 HAL_UART_Transmit(&huart1,out, sizeof(out), 100);
 HAL_Delay(1000);
 	flagCheck=1;

 ReRunMe(4);
}

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
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();

	firsttemp[0] = 0x11;
	secondtemp[0] = 0x12;
	//uint8_t tt[2];
	__HAL_UART_ENABLE_IT(&huart1,UART_IT_RXNE);
	Init();
  QueTask(&ReadTemp,0);
	QueTask(&CheckThreshold,1);
	QueTask(&toggleLED,2);
//	uint8_t tt = newQueue.currentTask[0].priority + '0';
//	HAL_UART_Transmit(&huart1,&tt,sizeof(tt),200);
//uint8_t tt1 = newQueue.currentTask[1].priority + '0';
//	HAL_UART_Transmit(&huart1,&tt,sizeof(tt1),200);
//uint8_t tt2 = newQueue.currentTask[2].priority + '0';
//	HAL_UART_Transmit(&huart1,&tt,sizeof(tt2),200);


	//uint8_t tt = newQueue.current_size + '0';
	//HAL_UART_Transmit(&huart1,&tt, sizeof(tt), 100);
	//QueTask(&CheckThreshold,1);
 while (1)
 {
	 
	 if (arrayCounter==2)
	 {Dispatch();}

 }

  
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
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
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Enable MSI Auto calibration
  */
  HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00000E14;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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
