#ifndef __MYIIC_H
#define __MYIIC_H
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
#include "common.h"




//IIC所有操作函数
void My_IIC_Init(void);                //初始化IIC的IO口				 
void My_IIC_Start(void);				//发送IIC开始信号
void My_IIC_Stop(void); 			//发送IIC停止信号
void My_IIC_Send_Byte(uint8 txdata);	//IIC发送一个字节
uint8 My_IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8 My_IIC_Wait_Ack(void); 				//IIC等待ACK信号
void My_IIC_Ack(void);					//IIC发送ACK信号
void My_IIC_NAck(void);				//IIC不发送ACK信号

void My_IIC_Write_One_Byte(uint8 daddr,uint8 addr,uint8 wdata);
uint8 My_IIC_Read_One_Byte(uint8 daddr,uint8 addr);	

//IO操作函数	 
#define IIC_SCL    P15 //SCL
#define IIC_SDA    P14 //SDA	 
#define READ_SDA   P14

#define SDA_IN()  {P1M0&=(~0x10);P1M1|=0x10;}
#define SDA_OUT() {P1M1&=(~0x10);P1M0|=0x10;}

//#define SDA_IN()  {;}
//#define SDA_OUT() {;}

#endif
















