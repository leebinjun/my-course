#include "lcd.h"
#include "delay.h"
#include "gui.h"
#include "test.h"
#include "touch.h"
#include "key.h" 
#include "led.h"
#include "pic.h"

#define xHorse 126
#define yHorse 42
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//测试硬件：单片机STM32F103RBT6,主频72M  单片机工作电压3.3V
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
//////////////////////////////////////////////////////////////////////////////////
//========================variable==========================//
u16 ColorTab[5]={BRED,YELLOW,RED,GREEN,BLUE};//定义颜色数组
//=====================end of variable======================//

//******************************************************************
//函数名：  DrawTestPage
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    绘制测试界面
//输入参数：str :字符串指针
//返回值：  无
//修改记录：
//******************************************************************
void DrawTestPage(u8 *str)
{
//绘制固定栏up
LCD_Fill(0,0,lcddev.width,20,BLUE);
//绘制固定栏down
LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
POINT_COLOR=WHITE;
Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"Student#:21724011",16,1);//居中显示
//绘制测试区域
LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
}

//******************************************************************
//函数名：  main_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    绘制全动电子综合测试程序主界面
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void main_test(void)
{
	DrawTestPage("全动电子综合测试程序");
	
	Gui_StrCenter(0,30,RED,BLUE,"全动电子",16,1);//居中显示
	Gui_StrCenter(0,60,RED,BLUE,"综合测试程序",16,1);//居中显示	
	Gui_StrCenter(0,90,YELLOW,BLUE,"3.5' ILI9486 320X480",16,1);//居中显示
	Gui_StrCenter(0,120,BLUE,BLUE,"xiaoFeng@QDtech 2014-02-25",16,1);//居中显示
	delay_ms(1500);		
	delay_ms(1500);
}

//******************************************************************
//函数名：  Test_Color
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    颜色填充测试，依次填充白色、黑色、红色、绿色、蓝色
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Color(void)
{
	DrawTestPage("测试1:纯色填充测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"White",16,1);delay_ms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLACK);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Black",16,1);delay_ms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,RED);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Red",16,1); delay_ms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,GREEN);
	Show_Str(lcddev.width-50,30,BLUE,YELLOW,"Green",16,1);delay_ms(500);
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,BLUE);
	Show_Str(lcddev.width-50,30,WHITE,YELLOW,"Blue",16,1);delay_ms(500);

}

//******************************************************************
//函数名：  Test_FillRec
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    矩形框显示和填充测试，依次显示粉红色、黄色、红色、绿色、蓝色矩形框，
//       	延时1500毫秒后，依次按照粉红色、黄色、红色、绿色、蓝色填充矩形框 
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************


u8 record[64][2] = {0};
u8 array[64][3] = 
{1, 1, 1,
2, 2, 3,
3, 1, 5,
4, 2, 7,
5, 4, 8,
6, 6, 7,
7, 8, 8,
8, 7, 6,
9, 6, 8,
10, 8, 7,
11, 7, 5,
12, 8, 3,
13, 7, 1,
14, 5, 2,
15, 3, 1,
16, 1, 2,
17, 2, 4,
18, 1, 6,
19, 2, 8,
20, 3, 6,
21, 1, 7,
22, 3, 8,
23, 5, 7,
24, 7, 8,
25, 8, 6,
26, 7, 4,
27, 8, 2,
28, 6, 1,
29, 4, 2,
30, 2, 1,
31, 1, 3,
32, 3, 2,
33, 5, 1,
34, 6, 3,
35, 8, 4,
36, 7, 2,
37, 5, 3,
38, 4, 1,
39, 2, 2,
40, 1, 4,
41, 3, 3,
42, 2, 5,
43, 4, 4,
44, 6, 5,
45, 4, 6,
46, 3, 4,
47, 5, 5,
48, 4, 3,
49, 6, 2,
50, 8, 1,
51, 7, 3,
52, 5, 4,
53, 3, 5,
54, 4, 7,
55, 2, 6,
56, 1, 8,
57, 3, 7,
58, 4, 5,
59, 6, 4,
60, 5, 6,
61, 7, 7,
62, 5, 8,
63, 6, 6,
64, 8, 5};
	
void Test_FillRec(void)
{
	
	
	u8 i=0,j=0,n=0;
	DrawTestPage("HomeWork2:KnightTour");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
  
	POINT_COLOR=ColorTab[4];
	for (i=0; i<8; i++) 
	{
		for (j=0; j<8; j++)
		{
			//LCD_DrawRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	    LCD_DrawRectangle(lcddev.width/2-120+(i*30),lcddev.height/2-120+(j*30),lcddev.width/2-120+(i*30)+30,lcddev.height/2-120+(j*30)+30); 
		}
	}

	POINT_COLOR=ColorTab[2];
  Gui_Drawbmp16(xHorse+array[0][1]*30-30,yHorse+array[0][2]*30-30,gImage_horse);
	delay_ms(500);
	for(i=1;i<64;i++)
	{

	  Gui_Drawbmp16(xHorse+array[i][1]*30-30,yHorse+array[i][2]*30-30,gImage_horse);
		Gui_Drawbmp16(xHorse+array[i-1][1]*30-30,yHorse+array[i-1][2]*30-30,gImage_hh);
		LCD_DrawLine(xHorse+array[i-1][1]*30-15, yHorse+array[i-1][2]*30-15,
                       		xHorse+array[i][1]*30-15,yHorse+array[i][2]*30-15);
	  for(j=1; j<i; j++)
	  {
				LCD_DrawLine(xHorse+array[j-1][1]*30-15, yHorse+array[j-1][2]*30-15,
                       		xHorse+array[j][1]*30-15,yHorse+array[j][2]*30-15);
		}
		delay_ms(500);
		
  }
	
	
	//Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
	
	/*
	DrawTestPage("测试6:图片显示测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30,30,gImage_qq);
	Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(90,30,gImage_qq);
	Show_Str(90+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,30,gImage_qq);
	Show_Str(150+12,75,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
	*/
	//delay_ms(1500);	
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	//for (i=0; i<5; i++) 
	//{
	//	LCD_DrawFillRectangle(lcddev.width/2-80+(i*15),lcddev.height/2-80+(i*15),lcddev.width/2-80+(i*15)+60,lcddev.height/2-80+(i*15)+60); 
	//	POINT_COLOR=ColorTab[i];
	//}
	delay_ms(1500);
}



//******************************************************************
//函数名：  Test_FillRec
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    圆形框显示和填充测试，依次显示粉红色、黄色、红色、绿色、蓝色圆形框，
//       	延时1500毫秒后，依次按照粉红色、黄色、红色、绿色、蓝色填充圆形框 
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Test_Circle(void)
{
	u8 i=0;
	DrawTestPage("测试3:GUI画圆填充测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	for (i=0; i<5; i++)  
		gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,0);
	delay_ms(1500);	
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE); 
	for (i=0; i<5; i++) 
	  	gui_circle(lcddev.width/2-80+(i*25),lcddev.height/2-50+(i*25),ColorTab[i],30,1);
	delay_ms(1500);
}

//******************************************************************
//函数名：  English_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    英文显示测试 
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void English_Font_test(void)
{
	DrawTestPage("测试4:英文显示测试");
	POINT_COLOR=RED;
	BACK_COLOR=BLUE;
	LCD_ShowString(10,30,12,"6X12:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,45,12,"6X12:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,60,12,"6X12:~!@#$%^&*()_+{}:<>?/|-+.",0);
	LCD_ShowString(10,80,16,"8X16:abcdefghijklmnopqrstuvwxyz0123456789",0);
	LCD_ShowString(10,100,16,"8X16:ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789",1);
	LCD_ShowString(10,120,16,"8X16:~!@#$%^&*()_+{}:<>?/|-+.",0); 
	delay_ms(1200);
}

//******************************************************************
//函数名：  Chinese_Font_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    中文显示测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Chinese_Font_test(void)
{	
	DrawTestPage("测试5:中文显示测试");
	Show_Str(10,30,BLUE,YELLOW,"16X16:全动电子技术有限公司欢迎您",16,0);
	Show_Str(10,50,BLUE,YELLOW,"16X16:Welcome全动电子",16,1);
	Show_Str(10,70,BLUE,YELLOW,"24X24:深圳市中文测试",24,1);
	Show_Str(10,100,BLUE,YELLOW,"32X32:字体测试",32,1);
	delay_ms(1200);
}

//******************************************************************
//函数名：  Pic_test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    图片显示测试，依次显示三幅40X40 QQ图像
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Pic_test(void)
{
	DrawTestPage("测试6:图片显示测试");
	LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
	Gui_Drawbmp16(30,30,gImage_qq);
	Show_Str(30+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(90,30,gImage_qq);
	Show_Str(90+12,75,BLUE,YELLOW,"QQ",16,1);
	Gui_Drawbmp16(150,30,gImage_qq);
	Show_Str(150+12,75,BLUE,YELLOW,"QQ",16,1);
	delay_ms(1200);
}

//******************************************************************
//函数名：  Touch_Test
//作者：    xiao冯@全动电子
//日期：    2013-02-22
//功能：    触摸手写测试
//输入参数：无
//返回值：  无
//修改记录：
//******************************************************************
void Touch_Test(void)
{
u8 key;
	u8 i=0;
	u16 j=0;
	u16 colorTemp=0;
TP_Init();
KEY_Init();
DrawTestPage("测试7:Touch测试");
LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,RED); 
POINT_COLOR=RED;
		while(1)
	{
	 	key=KEY_Scan();
		tp_dev.scan(0); 		 
		if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
		{	
		 	if(tp_dev.x<lcddev.width&&tp_dev.y<lcddev.height)
			{	
				if(tp_dev.x>(lcddev.width-24)&&tp_dev.y<16)
				{
					DrawTestPage("测试7:Touch测试");//清除
					LCD_ShowString(lcddev.width-24,0,16,"RST",1);//显示清屏区域
					POINT_COLOR=colorTemp;
					LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,POINT_COLOR); 
				}
				else if((tp_dev.x>(lcddev.width-60)&&tp_dev.x<(lcddev.width-50+20))&&tp_dev.y<20)
				{
				LCD_Fill(lcddev.width-52,2,lcddev.width-50+20,18,ColorTab[j%5]); 
				POINT_COLOR=ColorTab[(j++)%5];
				colorTemp=POINT_COLOR;
				delay_ms(10);
				}

				else TP_Draw_Big_Point(tp_dev.x,tp_dev.y,POINT_COLOR);		//画图	  			   
			}
		}else delay_ms(10);	//没有按键按下的时候 	    
		if(key==1)	//KEY_RIGHT按下,则执行校准程序
		{

			LCD_Clear(WHITE);//清屏
		    TP_Adjust();  //屏幕校准 
			TP_Save_Adjdata();	 
			DrawTestPage("测试7:Touch测试");
		}
		i++;
		if(i==20)
		{
			i=0;
			LED0=!LED0;
		}
	}   
}




