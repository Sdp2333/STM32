
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

#include "pid.h"
#include <stdio.h>
#include <math.h>
/*PID����*/
#define kp 0.86
#define ki 0.012
#define kd 0.005


int Timer = 0;			//ʱ��
uint8_t speed = 0;		//��ǰPWM
short TargetSpeed = 10; //Ŀ���ٶ�




/******************************
	���ܣ�ÿ5ms�ڶ�ʱ����ִ��һ�Σ�
				��ȡ����ٶ�SPEED
	����ֵ������ٶ�SPEED
	�βΣ���
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
	���ܣ�ÿ5ms�ڶ�ʱ����ִ��һ�Σ�
				����pwm����ֵ
	����ֵ������ٶ�SPEED
	�βΣ���
*******************************/
short PID_Cal(short Speed,short *error)
{
	short Error = TargetSpeed - Speed;
	static short Error_last = 0,Error_prev = 0;
	short pwm_add=0;
	*error = Error;
	pwm_add = kp*(Error - Error_last) + ki*Error + kd*(Error-2.0f*Error_last+Error_prev);
	
	Error_prev = Error_last;	  	    // �������ϴ����
  Error_last = Error;	              // �����ϴ�ƫ��
	
	
	return pwm_add;
}
/******************************
	���ܣ��жϵ������ת��
			�����������õ�PWM��ֵ
			д�뵥Ƭ����
	����ֵ����
	�βΣ���
*******************************/
void SetMotorVoltageAndDirection(int Pwm)
{
	if(Pwm<0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0); //����������Ÿ�1��0���з�ת
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);
	}
	else if(Pwm>0)
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);//����ת���и���
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4,0);
	}
	Pwm = fabs(Pwm);
  TIM1->CCR1 = Pwm;
}



/*�жϻص�����*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	short fSpeed;
	short ERROR;
	static uint8_t i = 0;
 	
 	/*�жϵ����붨ʱ��7�ж�ʱ*/
	if(htim->Instance == TIM7)
	{
		fSpeed = GetSpeed();			//��ȡ��ǰ�ٶ�	
		speed += PID_Cal(fSpeed,&ERROR);//��ǰPWM��ֵ��������ʽPID��������
		
		//����PWM���Χ
		if(speed>100)speed = 100;
		else if(speed<1)speed = 1;
		
		//��PID������PWMд��ϵͳ
		SetMotorVoltageAndDirection(speed);

		/* ÿ����5*100��ms��ӡһ���ٶ����� */
		i++;
		if(i >= 100)
		{
			i = 0;
			//Led_Toggle();Ҳ�����Լ����LED��˸�����鿴����
			printf("�ٶ�����Ϊ%d\n",fSpeed);
			printf("Ŀ���ٶ�Ϊ%d\n",TargetSpeed);
			printf("���Ϊ%d\n",ERROR);
		}
	}
	
	if(htim->Instance == TIM3)
	{
		
	}
}




