#include "Track.h"
#include "motor.h"
#include "xunji.h"
#include "openmv.h"
extern  int  Cx;

int ys=0,stop_flag=0;
void Tracking(void)
{
	   
		if(xj1==0&&xj2==0&&xj3==0&&xj4==0&&xj5==1)//
	  {
	  car_go_straight();		  //�����һ����ȡ�����ߣ�ֱ��
	  }
	 if(xj1==0&&xj2==1&&xj3==1&&xj4==0)//
	  {
	  car_go_straight();        //����м�������ȡ�����ߣ�ֱ��
	  }	  
		if(xj1==1&&xj2==0&&xj3==0&&xj4==0)//
	  {
	  car_go_left(); //�����һ����ȡ�����ߣ���ת
	 HAL_Delay(150);
		}
	 if(xj1==0&&xj2==1&&xj3==0&&xj4==0)//
	  {
	  car_go_left();   //����ڶ�����ȡ�����ߣ���ת
	  HAL_Delay(5);
	  }
		
		
 	 if(xj1==0&&xj2==0&&xj3==1&&xj4==0 )// //�����������ȡ�����ߣ���ת
	  {
	  car_go_right();  
	 HAL_Delay(5);
	  }
	  
	  if(xj1==0&&xj2==0&&xj3==0&&xj4==1)////������ĸ���ȡ�����ߣ���ת
	  {
	  car_go_right();   
	   HAL_Delay(150); 
	  }
		//����Ϊ��ͨѲ��
		
		
		
		
		
		
		
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1)////���ȫ����ȡ�������Ҷ�ȡ����������1����ת
	  {
			 car_go_straight(); 
			HAL_Delay(400);
	  car_go_left();   
	 HAL_Delay(950);
			ys=1;
			 car_go_straight();		  //�����û�ж�ȡ�������������ת�䣬ͣ�£���ͷ
	  HAL_Delay(1000);
			car_go_right();
			HAL_Delay(1900);
	  }
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==2)// //���ȫ����ȡ��������ʶ���������2����ת
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_right();  
	  HAL_Delay(950);
			ys=2;
			
	  }
		//����Ϊʶ��һ���ŷ�
		
		
		 if(xj1==0&&xj2==0&&xj3==0&&xj4==0&&xj5==0&&(ys==1||ys==2))//
	  {
	  car_go_ahead();		  //�����û�ж�ȡ�������������ת�䣬ͣ�£���ͷ
	  HAL_Delay(1000);
			car_go_right();
			HAL_Delay(1900);
				
	  }
		
		
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1&&ys==1)////һ�ŷ�����
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_right();   
	 HAL_Delay(950);
			stop_flag=2;
			ys=0; //��ձ�־λ
			
		}
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1&&ys==2)////���ŷ�����
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_left();   
	 HAL_Delay(950);
				stop_flag=2;
			ys=0; //��ձ�־λ
		}
		
			
		 if(xj1==0&&xj2==0&&xj3==0&&xj4==0&&stop_flag==2)//
	  {
	  car_go_ahead();		  //���غ�ͣ��
	  HAL_Delay(1000);
		
				
	  }
		
		
		
		
		
		
		
	  }
 
