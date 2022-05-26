/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
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

//board.h文件中FOSC的值设置为0,则程序自动识别系统频率

/*board.h文件中FOSC的值设置不为0，则系统频率为FOSC的值，
在使用stc-isp工具下载程序的时候需要将IRC频率设置为FOSC的值*/

/*在board_init中,已经将P54引脚设置为复位
如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可*/

#define LED0 P70
#define BEEP P11
uint8 key_scan(void)
{
    if((KEY0==0)||(KEY1==0)||(KEY2==0)||(KEY3==0))
	{
		delay_ms(10);//去抖动 
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
	return 0;// 无按键按下
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

