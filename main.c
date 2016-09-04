/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  MCD Application Team
  * @version V2.2.0
  * @date    30-September-2014
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 


/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"
#include "stm8s_gpio.h"
#include "stm8s_adc1.h"
#include "stm8s_tim2.h"
#include "stm8s_tim4.h"

/* Private defines -----------------------------------------------------------*/
uint32_t voltage;
uint32_t index;
uint32_t tmp_voltage;
uint32_t time;
uint32_t timer;
uint32_t led_timer;
uint32_t voltage_ok;


#define CONTROL_PORT GPIOB
#define CONTROL_PIN GPIO_PIN_4

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  
  IWDG_SetPrescaler(IWDG_Prescaler_256);
  IWDG_SetReload(0xFF);
  IWDG_WriteAccessCmd(IWDG_WriteAccess_Disable);
  IWDG_Enable();
  
  index = 0;
  timer = 0;
  voltage_ok = 0;
  
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  
  GPIO_Init(CONTROL_PORT, CONTROL_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
 
  if (RST_GetFlagStatus(RST_FLAG_WWDGF) == SET){
    //TODO delay
    RST_ClearFlag(RST_FLAG_WWDGF);
    
  }
  
  enableInterrupts();
  
  TIM4_DeInit();
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 0xFF);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  GPIO_WriteLow(GPIOB, GPIO_PIN_5);
  led_timer = 15;
  TIM4_Cmd(ENABLE);
  
  GPIO_WriteHigh(CONTROL_PORT, CONTROL_PIN); // mosfet control
  //GPIO_WriteLow(CONTROL_PORT, CONTROL_PIN);
    
  GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_FL_NO_IT); // ref AIN3
  GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_IN_FL_NO_IT); // vol AIN2

  TIM2_DeInit();
  TIM2_TimeBaseInit(TIM2_PRESCALER_32768, 611); // 29297
    // 611/(2000000/32768) = 10 sec
  // 29297/(16000000/32768) = 60,000256 sec

  TIM2_UpdateDisableConfig(DISABLE);
  TIM2_ITConfig(TIM2_IT_UPDATE, ENABLE);
  
   /* De-Init ADC1 peripheral */
  ADC1_DeInit();   
  ADC1_ScanModeCmd(ENABLE);
  ADC1_ITConfig(ADC1_IT_EOCIE, ENABLE);
  ADC1_Init(ADC1_CONVERSIONMODE_CONTINUOUS, 
            ADC1_CHANNEL_3,
            ADC1_PRESSEL_FCPU_D4, 
            ADC1_EXTTRIG_TIM, 
            DISABLE, 
            ADC1_ALIGN_RIGHT, 
            ADC1_SCHMITTTRIG_ALL,
            DISABLE);  
    
   ADC1_StartConversion();  
    
    
    
    // halt();

  /* Infinite loop */
  while (1)
  {
  }
  
}

#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
