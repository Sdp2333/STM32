#include "OpenMV.h"
#include "stdio.h"
#include "usart.h"
#include "oled.h"
#include "track.h"
uint8_t  Cx=0,Cy=0,Cw=0,Ch=0;
uint8_t K1_1[10];
uint8_t K2_2[10];
uint8_t K3_3[10];
uint8_t K4_4[10];

void   Openmv_Receive_Data(int16_t com_data)
{
  
    uint8_t i;
		static uint8_t RxCounter1=0;//计数
		static uint16_t RxBuffer1[10]={0};//初始化存储数组
		static uint8_t RxState = 0;	//状态
		static uint8_t RxFlag1 = 0;//标志位设置为0

  if(RxState==0&&com_data==0x2C&&RxFlag1 ==  0)  //0x2c帧头 开始接收
				{
          
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;//存储数据
         // HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);//存储时亮/灭灯
				}

				else if(RxState==1&&com_data==0x12)  //0x12帧头
				{
          //HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);//同上
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==2)
				{
           
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1接受满了,接收数据结束
					{
						RxState=3;
						RxFlag1=1;
            
						Cx=RxBuffer1[RxCounter1-5];
						Cy=RxBuffer1[RxCounter1-4];
						Cw=RxBuffer1[RxCounter1-3];
						Ch=RxBuffer1[RxCounter1-2];
					
//这个refresh很重要，没有他你的显示基本是不正常的
   
sprintf((char*)K1_1, "Cx:%.2f",(float) Cx);
sprintf((char*)K2_2, "Cy:%.2f",(float)Cy);
sprintf((char*)K3_3, "Cw:%.f", (float)Cw);
sprintf((char*)K4_4, "Ch:%.4f", (float)Ch);
OLED_ShowString(0,0,K1_1,16,0);//这个是oled驱动里面的，是显示位置的一个函数

OLED_ShowString(0,2,K2_2,16,0);//格式是（x轴，y轴，显示变量，16，1）

OLED_ShowString(0,4,K3_3,16,0);
						
OLED_ShowString(0,6,K4_4,16,0);			//详细的可以查看驱动文件，不细说了，这些函数基本都是套用
						
            //printf("%d\r   ",Cx);
            //printf("%d\r   ",Cy);
           // printf("%d\r   ",Cw);
           // printf("%d\r\n",Ch); 
//               if(RxState==1)
//          {
//            HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
//          }
//          else if(RxState!=1&&RxState!=0)
//          {
//            HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
//          }
				
					}
			}
		
				else if(RxState==3)		//检测是否接受到结束标志
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									
									RxFlag1 = 1;
									RxCounter1 = 0;
									RxState = 0;
								
						}
						else   //接收错误
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //将存放数据数组清零
									}
						}
				} 
	
				else   //接收异常
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //将存放数据数组清零
						}
				}
      }





