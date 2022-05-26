/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ��һȺ��179029047(����)  ��Ⱥ��244861897(����)  ��Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ790875685)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		MDK FOR C51 V9.60
 * @Target core		STC8H8K64S4
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-06-01
 ********************************************************************************************************************/

#include "headfile.h"
#define KEY0 P34
#define KEY1 P35
#define KEY2 P36
#define KEY3 P37
#define KEY0_PRESS 1
#define KEY1_PRESS 2
#define KEY2_PRESS 3
#define KEY3_PRESS 4
#define LED0 P70
#define LED1 P71
#define LED2 P72
#define LED3 P73

#define BEEP P11

//board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�ʶ��ϵͳƵ��

/*board.h�ļ���FOSC��ֵ���ò�Ϊ0����ϵͳƵ��ΪFOSC��ֵ��
��ʹ��stc-isp�������س����ʱ����Ҫ��IRCƵ������ΪFOSC��ֵ*/

/*��board_init��,�Ѿ���P54��������Ϊ��λ
�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����*/

#define LED0 P70
#define BEEP P11
uint8 key_scan(void)
{
    if((KEY0==0)||(KEY1==0)||(KEY2==0)||(KEY3==0))
	{
		delay_ms(10);//ȥ���� 
		if(KEY0==0)
		{
			while(!KEY0)
				;
            LED0=!LED0;
			return KEY0_PRESS;
		}
		if(KEY1==0)
		{
			while(!KEY1)
				;
            LED1=!LED1;
			return KEY1_PRESS;
		}
        if(KEY2==0)
		{
			while(!KEY2)
				;
            LED2=!LED2;
			return KEY2_PRESS;
		}
        if(KEY3==0)
		{
			while(!KEY3)
				;
            LED3=!LED3;
			return KEY3_PRESS;
		}
	} 	     
	return 0;// �ް�������
}


void main()
{
	DisableGlobalIRQ();
	board_init();
    
    
    P1M0=P1M0|0x02;//P11 pull-up out
    BEEP=1;
    delay_ms(200);
    BEEP=0;
    
	EnableGlobalIRQ();
    while(1)
	{
		delay_ms(100);
		LED0 = !LED0;
    }
}

