/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include "../../LibsUsphere/BSP_Drivers_Layer/Lis2dx12.h"
#include "../../LibsUsphere/API_Layer/Timeout.h"
#include <iostream>
#include <cmath>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

typedef enum fds_fsm_en
{
   INITIAL_STAGE_FALL_DETECTION_SYSTEM,
   WEIGHLESSNESS_FALL_DETECTION_SYSTEM,
   IMPACT_FALL_DETECTION_SYSTEM,
   MOTIONLESS_FALL_DETECTION_SYSTEM,

}fds_fsm_en_t;

/* USER CODE END PTD */
/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* Thresholds for fall detection stages */

#define WEIGHLESSNESS_THRESHOLD 0.45f /* Threshold for determining weightlessness stage */
#define IMPACT_THRESHOLD        2.1f  /* Threshold for determining impact stage */

#define INITIAL_FDS_TIME_SAMPLE 100   /* Initial time sample for fall detection system */
#define IMPACT_FDS_TIME_SAMPLE  20    /* Time sample for impact detection */
#define SAMPLING_TIMEOUT        10    /* Timeout duration for sampling */
#define MOTIONLESS_TIMEOUT      10000 /* Timeout duration in milliseconds for motionless stage */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

I2C_HandleTypeDef hi2c3;

UART_HandleTypeDef hlpuart1;

SUBGHZ_HandleTypeDef hsubghz;

Lis2dx12 lis2dx12;

CheckTimeout fdsSampleTimeout(SAMPLING_TIMEOUT);

acceleration_t acceleration;

uint16_t set_time_sample_accel = INITIAL_FDS_TIME_SAMPLE;

fds_fsm_en_t fds_fsm = INITIAL_STAGE_FALL_DETECTION_SYSTEM;

/*
   Class for Fall Detection System
   This class contains functions to handle different stages of fall detection.
 */
class FallDetection final{
public:

 /* Default constructor */
 FallDetection() = default;

 /* Function to handle initial stage of fall detection */
 void InitialStage();

 /* Function to handle weightlessness stage of fall detection */
 void WeightlessnessStage();

 /* Function to handle impact stage of fall detection */
 void ImpactStage();

 /* Function to handle motionless stage of fall detection */
 void MotionlessStage();

private:

 /* Private function to calculate vector sum */
 double CalculateVectorSum(const acceleration_t& acceleration);
};

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_LPUART1_UART_Init(void);
static void MX_I2C3_Init(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void FallDetection::InitialStage()
{
   /* Calculate vector sum based on acceleration data */
   double vector_sum = CalculateVectorSum(acceleration);

   /* Check if the vector sum is below the weighlessness threshold */
   if (vector_sum < WEIGHLESSNESS_THRESHOLD)
      fds_fsm = WEIGHLESSNESS_FALL_DETECTION_SYSTEM;
}
void FallDetection::WeightlessnessStage()
{
   /* Set time sample for acceleration data */
   set_time_sample_accel = IMPACT_FDS_TIME_SAMPLE; /* 20ms --> 50/sec */

   /* Set timeout for sampling */
   fdsSampleTimeout.setTimeout(SAMPLING_TIMEOUT);

   fds_fsm = IMPACT_FALL_DETECTION_SYSTEM;
}

void FallDetection::ImpactStage()
{
   /* Calculate vector sum based on acceleration data */
   double vector_sum = CalculateVectorSum(acceleration);

   /* Check if the vector sum is above the impact threshold, indicating a fall */
   if (vector_sum > IMPACT_THRESHOLD && 0 == fdsSampleTimeout.isUpdate())
   {
      fds_fsm = MOTIONLESS_FALL_DETECTION_SYSTEM;
      fdsSampleTimeout.setTimeout(MOTIONLESS_TIMEOUT);
   }
   else
   {
      fds_fsm = INITIAL_STAGE_FALL_DETECTION_SYSTEM;
   }
}

void FallDetection::MotionlessStage()
{
   /* Turn on the LED indicating the Fall Detection status */
   HAL_GPIO_WritePin(GPIOA,LED_MICRO_STS_Pin ,GPIO_PIN_SET);

   /* Wait to change state of the FSM */
   if (fdsSampleTimeout.isUpdate()
   {
      HAL_GPIO_WritePin(GPIOA,LED_MICRO_STS_Pin ,GPIO_PIN_RESET);
      fds_fsm = INITIAL_STAGE_FALL_DETECTION_SYSTEM;
   }
}

double FallDetection::CalculateVectorSum(const acceleration_t& acceleration)
{
   /* Calculate the squared values of each acceleration component */
   double x_squared = std::pow((acceleration.x_axis/1000.0), 2);
   double y_squared = std::pow((acceleration.y_axis/1000.0), 2);
   double z_squared = std::pow((acceleration.z_axis/1000.0), 2);

   /* Calculate the vector sum as the square root of the sum of squared components */
   double vector_sum = x_squared + y_squared + z_squared;

   /* Return the calculated vector sum */
   return std::sqrt(vector_sum);
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
   MX_LPUART1_UART_Init();
   MX_I2C3_Init();
  
   /* USER CODE BEGIN 2 */
   HAL_GPIO_WritePin(GPIOA,LED_MICRO_STS_Pin ,GPIO_PIN_RESET);
  
   lis2dx12.init();
  
   FallDetection fds;
  
   /* USER CODE END 2 */
  
   /* Infinite loop */
   /* USER CODE BEGIN WHILE */

   while (1)
   {
      lis2dx12.run(set_time_sample_accel);
  
      switch (fds_fsm)
      {
        case INITIAL_STAGE_FALL_DETECTION_SYSTEM:
            fds.InitialStage();
        break;
        
        case WEIGHLESSNESS_FALL_DETECTION_SYSTEM:
           fds.WeightlessnessStage();
        break;
    
        case IMPACT_FALL_DETECTION_SYSTEM:
           fds.ImpactStage();
        break;
    
        case MOTIONLESS_FALL_DETECTION_SYSTEM:
           fds.MotionlessStage();
        break;
  }
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
  
   /** Configure the main internal regulator output voltage
    */
   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
   /** Initializes the CPU, AHB and APB busses clocks
    */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
   RCC_OscInitStruct.HSEDiv = RCC_HSE_DIV1;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
   {
    Error_Handler();
   }
   /** Configure the SYSCLKSource, HCLK, PCLK1 and PCLK2 clocks dividers
    */
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK3|RCC_CLOCKTYPE_HCLK
     |RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1
     |RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSE;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
   RCC_ClkInitStruct.AHBCLK3Divider = RCC_SYSCLK_DIV1;
  
   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
   {
    Error_Handler();
   }
}

/**
 * @brief I2C3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_I2C3_Init(void)
{
  
   /* USER CODE BEGIN I2C3_Init 0 */
  
   /* USER CODE END I2C3_Init 0 */
  
   /* USER CODE BEGIN I2C3_Init 1 */
  
   /* USER CODE END I2C3_Init 1 */
   hi2c3.Instance = I2C3;
   hi2c3.Init.Timing = 0x00707CBB;
   hi2c3.Init.OwnAddress1 = 0;
   hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
   hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
   hi2c3.Init.OwnAddress2 = 0;
   hi2c3.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
   hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
   hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   if (HAL_I2C_Init(&hi2c3) != HAL_OK)
   {
    Error_Handler();
   }
   /** Configure Analogue filter
    */
   if (HAL_I2CEx_ConfigAnalogFilter(&hi2c3, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
   {
    Error_Handler();
   }
   /** Configure Digital filter
    */
   if (HAL_I2CEx_ConfigDigitalFilter(&hi2c3, 0) != HAL_OK)
   {
    Error_Handler();
   }
   /* USER CODE BEGIN I2C3_Init 2 */
  
   /* USER CODE END I2C3_Init 2 */

}

/**
 * @brief LPUART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_LPUART1_UART_Init(void)
{

   /* USER CODE BEGIN LPUART1_Init 0 */
  
   /* USER CODE END LPUART1_Init 0 */
  
   /* USER CODE BEGIN LPUART1_Init 1 */
  
   /* USER CODE END LPUART1_Init 1 */
   hlpuart1.Instance = LPUART1;
   hlpuart1.Init.BaudRate = 115200;
   hlpuart1.Init.WordLength = UART_WORDLENGTH_8B;
   hlpuart1.Init.StopBits = UART_STOPBITS_1;
   hlpuart1.Init.Parity = UART_PARITY_NONE;
   hlpuart1.Init.Mode = UART_MODE_TX_RX;
   hlpuart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   hlpuart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
   hlpuart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
   hlpuart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
   hlpuart1.FifoMode = UART_FIFOMODE_DISABLE;
   if (HAL_UART_Init(&hlpuart1) != HAL_OK)
   {
    Error_Handler();
   }
   if (HAL_UARTEx_SetTxFifoThreshold(&hlpuart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
   {
    Error_Handler();
   }
   if (HAL_UARTEx_SetRxFifoThreshold(&hlpuart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
   {
    Error_Handler();
   }
   if (HAL_UARTEx_DisableFifoMode(&hlpuart1) != HAL_OK)
   {
    Error_Handler();
   }
   /* USER CODE BEGIN LPUART1_Init 2 */
  
   /* USER CODE END LPUART1_Init 2 */

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
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
  
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOA, LED_MICRO_STS_Pin|SPI1_NSS_Pin|WP_MEM_Pin|HOLD_MEM_Pin, GPIO_PIN_RESET);
  
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(BOOT_GPIO_Port, BOOT_Pin, GPIO_PIN_RESET);
  
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOB, RF_SWITCH_CTRL_Pin|UD5_MICRO_DIG_OUT2_Pin, GPIO_PIN_RESET);
  
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(UD4_MICRO_DIG_OUT1_GPIO_Port, UD4_MICRO_DIG_OUT1_Pin, GPIO_PIN_RESET);
  
   /*Configure GPIO pins : UD1_MICRO_DIG_IN1_Pin UD2_MICRO_DIG_IN2_Pin UD3_MICRO_DIG_IN3_Pin */
   GPIO_InitStruct.Pin = UD1_MICRO_DIG_IN1_Pin|UD2_MICRO_DIG_IN2_Pin|UD3_MICRO_DIG_IN3_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
   /*Configure GPIO pins : LED_MICRO_STS_Pin SPI1_NSS_Pin WP_MEM_Pin HOLD_MEM_Pin */
   GPIO_InitStruct.Pin = LED_MICRO_STS_Pin|SPI1_NSS_Pin|WP_MEM_Pin|HOLD_MEM_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  
   /*Configure GPIO pin : BOOT_Pin */
   GPIO_InitStruct.Pin = BOOT_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_PULLDOWN;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(BOOT_GPIO_Port, &GPIO_InitStruct);
  
   /*Configure GPIO pins : RF_SWITCH_CTRL_Pin UD5_MICRO_DIG_OUT2_Pin */
   GPIO_InitStruct.Pin = RF_SWITCH_CTRL_Pin|UD5_MICRO_DIG_OUT2_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
   /*Configure GPIO pin : UD4_MICRO_DIG_OUT1_Pin */
   GPIO_InitStruct.Pin = UD4_MICRO_DIG_OUT1_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(UD4_MICRO_DIG_OUT1_GPIO_Port, &GPIO_InitStruct);
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
