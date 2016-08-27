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

/* Private defines -----------------------------------------------------------*/
uint32_t voltage;
uint32_t index;
uint32_t tmp_voltage;
uint32_t time;
uint32_t timer;


#define CONTROL_PORT GPIOB
#define CONTROL_PIN GPIO_PIN_4

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void main(void)
{
  index = 0;
  timer = 0;
  
  GPIO_DeInit(GPIOA);
  GPIO_DeInit(GPIOB);
  GPIO_DeInit(GPIOC);
  GPIO_DeInit(GPIOD);
  
  
  GPIO_Init(CONTROL_PORT, CONTROL_PIN, GPIO_MODE_OUT_PP_HIGH_FAST);
  GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_SLOW);
  while(1){
    
    volatile uint32_t i = 0x2FFF;
    GPIO_WriteLow(CONTROL_PORT, CONTROL_PIN); 
    GPIO_WriteLow(GPIOB, GPIO_PIN_5); // led
    while(i--){
     
    };
    GPIO_WriteHigh(CONTROL_PORT, CONTROL_PIN); 
    GPIO_WriteHigh(GPIOB, GPIO_PIN_5); 
     i = 0x2FFF;
    while(i--){
     
    };
  }
  
  return;
 
  
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
