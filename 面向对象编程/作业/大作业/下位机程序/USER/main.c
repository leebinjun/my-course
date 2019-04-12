#include "delay.h"
#include "sys.h"
#include "key.h"
#include "lcd.h"
#include "touch.h"
#include "gui.h"
#include "test.h"
#include "uart.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,正点原子MiniSTM32开发板,主频72MHZ
//QDtech-TFT液晶驱动 for STM32 IO模拟
//xiao冯@ShenZhen QDtech co.,LTD
//公司网站:www.qdtech.net
//淘宝网站：http://qdtech.taobao.com
//我司提供技术支持，任何技术问题欢迎随时交流学习
//固话(传真) :+86 0755-23594567 
//手机:15989313508（冯工） 
//邮箱:QDtech2008@gmail.com 
//Skype:QDtech2008
//技术交流QQ群:324828016
//创建日期:2013/5/13
//版本：V1.1
//版权所有，盗版必究。
//Copyright(C) 深圳市全动电子技术有限公司 2009-2019
//All rights reserved
/****************************************************************************************************
//=======================================液晶屏数据线接线==========================================//
//DB0       接PD14 
//DB1       接PD15 
//DB2       接PD0 
//DB3       接PD1 
//DB4~DB12  依次接PE7~PE15
//DB13      接PD8 
//DB14      接PD9
//DB15      接PD10  
//=======================================液晶屏控制线接线==========================================//
//LCD_CS	接PG12	//片选信号
//LCD_RS	接PG0	//寄存器/数据选择信号
//LCD_WR	接PD5	//写信号
//LCD_RD	接PD4	//读信号
//LCD_RST	接PC5	//复位信号
//LCD_LED	接PB0	//背光控制信号(高电平点亮)
//=========================================触摸屏触接线=========================================//
//不使用触摸或者模块本身不带触摸，则可不连接
//MO(MISO)	接PF8	//SPI总线输出
//MI(MOSI)	接PF9	//SPI总线输入
//PEN		接PF10	//触摸屏中断信号
//TCS		接PB2	//触摸IC片选
//CLK		接PB1	//SPI总线时钟
**************************************************************************************************/	



int main(void)
{	//u16 i=100;	
	//SystemInit();//初始化RCC 设置系统主频为72MHZ
	u8 i;
	u8 len;
  u8 key;	
	u16 times=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();	     //延时初始化
	LCD_Init();	   //液晶屏初始化 

		
//	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级

	uart_init(115200);	 //串口初始化为9600
	
	while(0)
	{
	  key=KEY_Scan();  //扫描KEY1 
		if(key==1)//KEY1按下,向USART1发送数据D
		{
 			//LCD_ShowString(30,90,200,16,16,"Data From USART1:");	//提示从UART1接收到的数据 BUF		
			USART_SendData(USART1,'D');
			delay_ms(100);
			
		}		
		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n\r\n");
			for(i=0;i<len;i++)
			{
				USART_SendData(USART1, USART_RX_BUF[i]);//向串口1发送数据
				USART_SendData(USART1, 12);//向串口1发送数据
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0; 
		}
        else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\n我测试的例程\r\n");
				printf("Beetle\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\n");  
			delay_ms(10);   
		}
		
		
	}
	
	Test_FillRec();		//GUI矩形绘图测试
//	while(1)
//	{	
//		main_test(); 		//测试主界面
//		Test_Color();  		//简单刷屏填充测试
//		Test_FillRec();		//GUI矩形绘图测试
//		Test_Circle(); 		//GUI画圆测试
//		English_Font_test();//英文字体示例测试
//		Chinese_Font_test();//中文字体示例测试
//		Pic_test();			//图片显示示例测试
	//	Touch_Test();		//触摸屏手写测试  
//	}				  
	
 }

