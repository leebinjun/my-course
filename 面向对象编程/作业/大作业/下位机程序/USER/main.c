#include "delay.h"
#include "sys.h"
#include "key.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "uart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����Ӳ������Ƭ��STM32F103RBT6,����ԭ��MiniSTM32������,��Ƶ72MHZ
//QDtech-TFTҺ������ for STM32 IOģ��
//xiao��@ShenZhen QDtech co.,LTD
//��˾��վ:www.qdtech.net
//�Ա���վ��http://qdtech.taobao.com
//��˾�ṩ����֧�֣��κμ������⻶ӭ��ʱ����ѧϰ
//�̻�(����) :+86 0755-23594567 
//�ֻ�:15989313508���빤�� 
//����:QDtech2008@gmail.com 
//Skype:QDtech2008
//��������QQȺ:324828016
//��������:2013/5/13
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) ������ȫ�����Ӽ������޹�˾ 2009-2019
//All rights reserved
/****************************************************************************************************
//=======================================Һ���������߽���==========================================//
//DB0       ��PD14 
//DB1       ��PD15 
//DB2       ��PD0 
//DB3       ��PD1 
//DB4~DB12  ���ν�PE7~PE15
//DB13      ��PD8 
//DB14      ��PD9
//DB15      ��PD10  
//=======================================Һ���������߽���==========================================//
//LCD_CS	��PG12	//Ƭѡ�ź�
//LCD_RS	��PG0	//�Ĵ���/����ѡ���ź�
//LCD_WR	��PD5	//д�ź�
//LCD_RD	��PD4	//���ź�
//LCD_RST	��PC5	//��λ�ź�
//LCD_LED	��PB0	//��������ź�(�ߵ�ƽ����)
//=========================================������������=========================================//
//��ʹ�ô�������ģ�鱾������������ɲ�����
//MO(MISO)	��PF8	//SPI�������
//MI(MOSI)	��PF9	//SPI��������
//PEN		��PF10	//�������ж��ź�
//TCS		��PB2	//����ICƬѡ
//CLK		��PB1	//SPI����ʱ��
**************************************************************************************************/	



int main(void)
{	//u16 i=100;	
	//SystemInit();//��ʼ��RCC ����ϵͳ��ƵΪ72MHZ
	u8 i;
	u8 len;
  u8 key;	
	u16 times=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	     //��ʱ��ʼ��
	LCD_Init();	   //Һ������ʼ�� 

		
//	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�

	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600
	
	while(0)
	{
	  key=KEY_Scan();  //ɨ��KEY1 
		if(key==1)//KEY1����,��USART1��������D
		{
 			//LCD_ShowString(30,90,200,16,16,"Data From USART1:");	//��ʾ��UART1���յ������� BUF		
			USART_SendData(USART1,'D');
			delay_ms(100);
			
		}		
		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n\r\n");
			for(i=0;i<len;i++)
			{
				USART_SendData(USART1, USART_RX_BUF[i]);//�򴮿�1��������
				USART_SendData(USART1, 12);//�򴮿�1��������
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0; 
		}
        else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n�Ҳ��Ե�����\r\n");
				printf("Beetle\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\n");  
			delay_ms(10);   
		}
		
		
	}
	
	Test_FillRec();		//GUI���λ�ͼ����
//	while(1)
//	{	
//		main_test(); 		//����������
//		Test_Color();  		//��ˢ��������
//		Test_FillRec();		//GUI���λ�ͼ����
//		Test_Circle(); 		//GUI��Բ����
//		English_Font_test();//Ӣ������ʾ������
//		Chinese_Font_test();//��������ʾ������
//		Pic_test();			//ͼƬ��ʾʾ������
	//	Touch_Test();		//��������д����  
//	}				  
	
 }

