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
	  car_go_straight();		  //如果就一个读取到黑线，直走
	  }
	 if(xj1==0&&xj2==1&&xj3==1&&xj4==0)//
	  {
	  car_go_straight();        //如果中间两个读取到黑线，直走
	  }	  
		if(xj1==1&&xj2==0&&xj3==0&&xj4==0)//
	  {
	  car_go_left(); //如果第一个读取到黑线，左转
	 HAL_Delay(150);
		}
	 if(xj1==0&&xj2==1&&xj3==0&&xj4==0)//
	  {
	  car_go_left();   //如果第二个读取到黑线，左转
	  HAL_Delay(5);
	  }
		
		
 	 if(xj1==0&&xj2==0&&xj3==1&&xj4==0 )// //如果第三个读取到黑线，右转
	  {
	  car_go_right();  
	 HAL_Delay(5);
	  }
	  
	  if(xj1==0&&xj2==0&&xj3==0&&xj4==1)////如果第四个读取到黑线，右转
	  {
	  car_go_right();   
	   HAL_Delay(150); 
	  }
		//以上为普通巡线
		
		
		
		
		
		
		
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1)////如果全部读取到黑线且读取到的数字是1，左转
	  {
			 car_go_straight(); 
			HAL_Delay(400);
	  car_go_left();   
	 HAL_Delay(950);
			ys=1;
			 car_go_straight();		  //如果都没有读取到黑线且已完成转弯，停下，掉头
	  HAL_Delay(1000);
			car_go_right();
			HAL_Delay(1900);
	  }
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==2)// //如果全部读取到黑线且识别的数字是2，右转
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_right();  
	  HAL_Delay(950);
			ys=2;
			
	  }
		//以上为识别一二号房
		
		
		 if(xj1==0&&xj2==0&&xj3==0&&xj4==0&&xj5==0&&(ys==1||ys==2))//
	  {
	  car_go_ahead();		  //如果都没有读取到黑线且已完成转弯，停下，掉头
	  HAL_Delay(1000);
			car_go_right();
			HAL_Delay(1900);
				
	  }
		
		
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1&&ys==1)////一号房返回
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_right();   
	 HAL_Delay(950);
			stop_flag=2;
			ys=0; //清空标志位
			
		}
		if(xj1==1&&xj2==1&&xj3==1&&xj4==1&&Cx==1&&ys==2)////二号房返回
	  {
			 car_go_straight(); 
			HAL_Delay(180);
	  car_go_left();   
	 HAL_Delay(950);
				stop_flag=2;
			ys=0; //清空标志位
		}
		
			
		 if(xj1==0&&xj2==0&&xj3==0&&xj4==0&&stop_flag==2)//
	  {
	  car_go_ahead();		  //返回后，停下
	  HAL_Delay(1000);
		
				
	  }
		
		
		
		
		
		
		
	  }
 
