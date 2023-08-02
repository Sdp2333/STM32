
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "pid.h"
#include <stdio.h>
#include <math.h>
/*PID参数*/
#define kp 0.86
#define ki 0.012
#define kd 0.005


int Timer = 0;			//时间
uint8_t speed = 0;		//当前PWM
short TargetSpeed = 10; //目标速度




/******************************
	功能：每5ms在定时器中执行一次，
				获取电机速度SPEED
	返回值：电机速度SPEED
	形参：无
*******************************/
short GetSpeed()
{
	short SPEED = 0;
//	static short last = 0;
	SPEED = (short)(__HAL_TIM_GET_COUNTER(&htim3)*100)/(4*16*10);
	__HAL_TIM_SET_COUNTER(&htim3,0);
	return SPEED;
}


/******************************
	功能：每5ms在定时器中执行一次，
				计算pwm返回值
	返回值：电机速度SPEED
	形参：无
*******************************/
short PID_Cal(short Speed,short *error)
{
	short Error = TargetSpeed - Speed;
	static short Error_last = 0,Error_prev = 0;
	short pwm_add=0;
	*error = Error;
	pwm_add = kp*(Error - Error_last) + ki*Error + kd*(Error-2.0f*Error_last+Error_prev);
	
	Error_prev = Error_last;	  	    // 保存上上次误差
  Error_last = Error;	              // 保存上次偏差
	
	
	return pwm_add;
}
/******************************
	功能：判断电机正反转，
			并将计算所得的PWM数值
			写入单片机中
	返回值：无
	形参：无
*******************************/
void SetMotorVoltageAndDirection(int Pwm)
{
	if(Pwm<0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0); //电机驱动引脚给1或0进行翻转
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);
	}
	else if(Pwm>0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);//正反转自行更改
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);
	}
	Pwm = fabs(Pwm);
  TIM1->CCR1 = Pwm;
}



/*中断回调函数*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	short fSpeed;
	short ERROR;
	static uint8_t i = 0;
 	
 	/*判断当进入定时器7中断时*/
	if(htim->Instance == TIM7)
	{
		fSpeed = GetSpeed();			//获取当前速度	
		speed += PID_Cal(fSpeed,&ERROR);//当前PWM数值加上增量式PID计算所得
		
		//限制PWM最大范围
		if(speed>100)speed = 100;
		else if(speed<1)speed = 1;
		
		//将PID计算后的PWM写入系统
		SetMotorVoltageAndDirection(speed);

		/* 每隔（5*100）ms打印一次速度数据 */
		i++;
		if(i >= 100)
		{
			i = 0;
			//Led_Toggle();也可以自己编个LED闪烁函数查看现象
			printf("速度数据为%d\n",fSpeed);
			printf("目标速度为%d\n",TargetSpeed);
			printf("误差为%d\n",ERROR);
		}
	}
	
	if(htim->Instance == TIM3)
	{
		
	}
}




