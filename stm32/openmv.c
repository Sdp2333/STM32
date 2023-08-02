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
		static uint8_t RxCounter1=0;//����
		static uint16_t RxBuffer1[10]={0};//��ʼ���洢����
		static uint8_t RxState = 0;	//״̬
		static uint8_t RxFlag1 = 0;//��־λ����Ϊ0

  if(RxState==0&&com_data==0x2C&&RxFlag1 ==  0)  //0x2c֡ͷ ��ʼ����
				{
          
					RxState=1;
					RxBuffer1[RxCounter1++]=com_data;//�洢����
         // HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);//�洢ʱ��/���
				}

				else if(RxState==1&&com_data==0x12)  //0x12֡ͷ
				{
          //HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);//ͬ��
					RxState=2;
					RxBuffer1[RxCounter1++]=com_data;
				}
				else if(RxState==2)
				{
           
					RxBuffer1[RxCounter1++]=com_data;
					if(RxCounter1>=10||com_data == 0x5B)       //RxBuffer1��������,�������ݽ���
					{
						RxState=3;
						RxFlag1=1;
            
						Cx=RxBuffer1[RxCounter1-5];
						Cy=RxBuffer1[RxCounter1-4];
						Cw=RxBuffer1[RxCounter1-3];
						Ch=RxBuffer1[RxCounter1-2];
					
//���refresh����Ҫ��û���������ʾ�����ǲ�������
   
sprintf((char*)K1_1, "Cx:%.2f",(float) Cx);
sprintf((char*)K2_2, "Cy:%.2f",(float)Cy);
sprintf((char*)K3_3, "Cw:%.f", (float)Cw);
sprintf((char*)K4_4, "Ch:%.4f", (float)Ch);
OLED_ShowString(0,0,K1_1,16,0);//�����oled��������ģ�����ʾλ�õ�һ������

OLED_ShowString(0,2,K2_2,16,0);//��ʽ�ǣ�x�ᣬy�ᣬ��ʾ������16��1��

OLED_ShowString(0,4,K3_3,16,0);
						
OLED_ShowString(0,6,K4_4,16,0);			//��ϸ�Ŀ��Բ鿴�����ļ�����ϸ˵�ˣ���Щ����������������
						
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
		
				else if(RxState==3)		//����Ƿ���ܵ�������־
				{
						if(RxBuffer1[RxCounter1-1] == 0x5B)
						{
									
									RxFlag1 = 1;
									RxCounter1 = 0;
									RxState = 0;
								
						}
						else   //���մ���
						{
									RxState = 0;
									RxCounter1=0;
									for(i=0;i<10;i++)
									{
											RxBuffer1[i]=0x00;      //�����������������
									}
						}
				} 
	
				else   //�����쳣
				{
						RxState = 0;
						RxCounter1=0;
						for(i=0;i<10;i++)
						{
								RxBuffer1[i]=0x00;      //�����������������
						}
				}
      }





