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

//board.h�ļ���FOSC��ֵ����Ϊ0,������Զ�ʶ��ϵͳƵ��

/*board.h�ļ���FOSC��ֵ���ò�Ϊ0����ϵͳƵ��ΪFOSC��ֵ��
��ʹ��stc-isp�������س����ʱ����Ҫ��IRCƵ������ΪFOSC��ֵ*/

/*��board_init��,�Ѿ���P54��������Ϊ��λ
�����Ҫʹ��P54����,������board.c�ļ��е�board_init()������ɾ��SET_P54_RESRT����*/

uint16 adc_data[4];
void main()
{
	DisableGlobalIRQ();	//�ر����ж�
	board_init();	
	
    oled_init(); 
	oled_p6x8str(0,0,"init success");
    oled_cls();
    
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	adc_init(ADC_P01, ADC_SYSclk_DIV_2);
    adc_init(ADC_P02, ADC_SYSclk_DIV_2);
	adc_init(ADC_P03, ADC_SYSclk_DIV_2);
	
	EnableGlobalIRQ();	//�������ж�
	
    while(1)
	{
		adc_data[0] = adc_once(ADC_P00, ADC_12BIT);
        oled_p6x8num(0,0,adc_data[0]);
        adc_data[1] = adc_once(ADC_P01, ADC_12BIT);
        oled_p6x8num(0,1,adc_data[1]);
        adc_data[2] = adc_once(ADC_P02, ADC_12BIT);
        oled_p6x8num(0,2,adc_data[2]);
        adc_data[3] = adc_once(ADC_P03, ADC_12BIT);
        oled_p6x8num(0,3,adc_data[3]);
    }
}

