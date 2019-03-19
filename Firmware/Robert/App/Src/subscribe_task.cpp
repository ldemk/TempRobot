/*
 * subscribe_task.cpp
 *
 *  Created on: Mar 18, 2019
 *      Author:
 */

#include "subscribe_task.h"

static ros::NodeHandle *nh_;

void led_cb(const std_msgs::UInt16& cmd_msg);

ros::Subscriber<std_msgs::UInt16> sub_led("led", led_cb);

void led_cb(const std_msgs::UInt16& cmd_msg)
{
    /* debug code: */

	switch(cmd_msg.data)
	{
		case 0: HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET); break;
		case 1: HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET); break;
	}

}

void ROS_SubscribeTaskHandler(void const * argument)
{

  /* USER CODE BEGIN ROS_SpinTaskHandler */

  /* Infinite loop */
  for(;;)
  {
	  osDelay(100);
  }
  /* USER CODE END ROS_SpinTaskHandler */
}



uint32_t subscribeInitTask(ros::NodeHandle *nh)
{
	osThreadId ROS_SubscribeTaskHandle;

	 nh_ = nh;
	 nh_->subscribe(sub_led);

	 /* definition and creation of ROS_SpinTask */
	 osThreadDef(ROS_SubscribeTask, ROS_SubscribeTaskHandler, osPriorityIdle, 0, 128);
	 ROS_SubscribeTaskHandle = osThreadCreate(osThread(ROS_SubscribeTask), NULL);
	 if (NULL == ROS_SubscribeTaskHandle)
	 {
	 	return 1;
	 }

	 return 0;

}
