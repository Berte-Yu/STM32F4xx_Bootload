/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
#include "flash_if.h"
#include "bootload_config.h"
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
typedef void (*pFunction)(void);

pFunction JumpToApplication;

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

int fputc(int ch, FILE *f)
 {
		HAL_UART_Transmit(&huart1, (uint8_t *)&ch,1,100);
		return (ch);
 }

uint8_t SetParamToFlash(BootLoad_PARAM* bt)
{
	uint8_t res = 0;
  res = flash_if_erase(BOOTLOAD_PARAM_ADD,sizeof(BootLoad_PARAM));
	if(res != 0)
	{
		res = 1;
		goto exit_SPTF;
	}
  res = flash_if_write(BOOTLOAD_PARAM_ADD, (uint32_t *)bt, sizeof(BootLoad_PARAM));
	if(res != 0)
	{
		res = 2;
	}
	
	exit_SPTF:	
  return res;
}

uint8_t GetParamFromFlash(BootLoad_PARAM* bt)
{
    flash_if_read(BOOTLOAD_PARAM_ADD, (uint32_t*)&bt, sizeof(BootLoad_PARAM));

    return 0;
}

void Reset_MCU(void)
{
  __set_FAULTMASK(1);
  NVIC_SystemReset();
  while(1);
}

uint8_t CopyAppHandler(BootLoad_PARAM* bt)
{
  //将下载区的程序拷贝到APP�?
	return 0;
}

void GotoAppHandler(BootLoad_PARAM* bt)
{
  uint32_t JumpAddress;

  JumpAddress = *(__IO uint32_t*) (bt->APP_ADD + 4);

  JumpToApplication = (pFunction)JumpAddress;

  __set_MSP(*(__IO uint32_t*) bt->APP_ADD);
  
  HAL_RCC_DeInit();

  JumpToApplication();
  
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  BootLoad_PARAM BT_PARAM;
	uint8_t res = 0;
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  printf("STM32F4xx_bootload\r\n");
	printf("clock is HSI,168M\r\n");
	
	printf("Get ParamFromFlash...\r\n");
  GetParamFromFlash(&BT_PARAM);
	
	printf("The APP_ADDESS is 0x%x.\r\n",BT_PARAM.APP_ADD);
	printf("The APP_SIZE is 0x%x.\r\n",BT_PARAM.APP_SIZE);
	printf("The DOWNLOAD_ADDESS is 0x%x.\r\n",BT_PARAM.DOWN_LOAD_ADD);
	printf("The DOWNLOAD_SIZE is 0x%x.\r\n",BT_PARAM.DOWN_LOAD_SIZE);
	
  switch (BT_PARAM.Status)
  {
      case GOTO_APP:
				printf("GO TO APP NOW.\r\n");
        GotoAppHandler(&BT_PARAM);
        break;
      case COPY_APP:
        break;
			default:
				printf("bootload is not init.\r\n");
				printf("set the param to default.\r\n");
				BT_PARAM.APP_ADD = default_APP_ADD;
        BT_PARAM.APP_SIZE = default_APP_SIZE;
        BT_PARAM.DOWN_LOAD_ADD = default_DOWN_LOAD_ADD;
        BT_PARAM.DOWN_LOAD_SIZE = default_DOWN_LOAD_SIZE;
        BT_PARAM.Status = GOTO_APP;
				res = SetParamToFlash(&BT_PARAM);
				if(res == 1)
				{
					printf("SetParam ERROR: flash erase fault.\r\n");
					while(1);
				}
				else if(res == 2)
				{
					printf("SetParam ERROR: flash write fault.\r\n");
					while(1);
				}
				printf("SetParam OK\r\n");
				printf("MCU Reset NOW.");
				Reset_MCU();
				break;
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
  huart1.Init.Mode = UART_MODE_TX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
