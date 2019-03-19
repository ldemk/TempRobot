/*
 * hearbeat_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include "hearbeat_task.h"


void Heartbeat_TaskHandler(void const * argument)
{
  /* USER CODE BEGIN Heartbeat_TaskHandler */
  /* This task shows that CPU works */

  /* Infinite loop */
  for(;;)
  {
	  HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
	  osDelay(600);
  }

  /* USER CODE END Heartbeat_TaskHandler */
}


uint32_t heartbeetInitTask(void)
{
	osThreadId Heartbeat_TaskHandle;

	osThreadDef(Heartbeat_Task, Heartbeat_TaskHandler, osPriorityIdle, 0, 128);
	Heartbeat_TaskHandle = osThreadCreate(osThread(Heartbeat_Task), NULL);
	if (NULL == Heartbeat_TaskHandle)
	{
		return 1;
	}
	return 0;
}
