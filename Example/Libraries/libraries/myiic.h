#ifndef __MYIIC_H
#define __MYIIC_H
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
#include "common.h"




//IIC���в�������
void My_IIC_Init(void);                //��ʼ��IIC��IO��				 
void My_IIC_Start(void);				//����IIC��ʼ�ź�
void My_IIC_Stop(void); 			//����IICֹͣ�ź�
void My_IIC_Send_Byte(uint8 txdata);	//IIC����һ���ֽ�
uint8 My_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8 My_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void My_IIC_Ack(void);					//IIC����ACK�ź�
void My_IIC_NAck(void);				//IIC������ACK�ź�

void My_IIC_Write_One_Byte(uint8 daddr,uint8 addr,uint8 wdata);
uint8 My_IIC_Read_One_Byte(uint8 daddr,uint8 addr);	

//IO��������	 
#define IIC_SCL    P15 //SCL
#define IIC_SDA    P14 //SDA	 
#define READ_SDA   P14

#define SDA_IN()  {P1M0&=(~0x10);P1M1|=0x10;}
#define SDA_OUT() {P1M1&=(~0x10);P1M0|=0x10;}

//#define SDA_IN()  {;}
//#define SDA_OUT() {;}

#endif
















