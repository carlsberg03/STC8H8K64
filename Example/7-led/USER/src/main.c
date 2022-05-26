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

//board.h文件中FOSC的值设置为0,则程序自动识别系统频率

/*board.h文件中FOSC的值设置不为0，则系统频率为FOSC的值，
在使用stc-isp工具下载程序的时候需要将IRC频率设置为FOSC的值*/

/*在board_init中,已经将P54引脚设置为复位
如果需要使用P54引脚,可以在board.c文件中的board_init()函数中删除SET_P54_RESRT即可*/

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

uint16 duty[5];
void main()
{
	DisableGlobalIRQ();	//关闭总中断
	board_init();	
	
	pwm_init(PWM7_P33, 50, 0);//舵机,初始化PWM7  使用引脚P3.3  输出PWM频率50HZ   占空比为百分之 5000/PWM_DUTY_MAX*100
    
    pwm_init(PWM1P_P20, 500, 6000);//电机1
    pwm_init(PWM2P_P22, 500, 6000);//电机2
    pwm_init(PWM3P_P24, 500, 6000);//电机3
    pwm_init(PWM4P_P26, 500, 6000);//电机4
    
    pwm_init(PWM1N_P21, 500, 3000);
    pwm_init(PWM2N_P23, 500, 3000);   
    pwm_init(PWM3N_P25, 500, 3000);
    pwm_init(PWM4N_P27, 500, 3000);
    
    
    duty[0]=5000;
    duty[1]=5000;
    duty[2]=5000;
    duty[3]=5000;
    duty[4]=800;
    
    pwm_duty(PWM1P_P20, duty[0]);
    pwm_duty(PWM2P_P22, duty[1]);
    pwm_duty(PWM3P_P24, duty[2]);
    pwm_duty(PWM4P_P26, duty[3]);
    pwm_duty(PWM7_P33, duty[4]);
    
    oled_init(); 
	oled_p6x8str(0,0,"init success");
    oled_cls();

	EnableGlobalIRQ();	//开启总中断
    while(1)
	{  
        oled_p6x8num(0,4,duty[0]);
        oled_p6x8num(0,5,duty[1]);
        oled_p6x8num(0,6,duty[2]);
        oled_p6x8num(0,7,duty[3]);
        oled_p6x8num(64,7,duty[4]);
        switch(key_scan())
        {
            case KEY0_PRESS:
            {
                if(duty[0]==8000)
                {
                    duty[0]=2000;
                    pwm_duty(PWM1P_P20, 5000);//反转时先刹车
                    delay_ms(200);
                }
                else
                    duty[0]+=100;
                pwm_duty(PWM1P_P20, duty[0]);
                break;
            }
            case KEY1_PRESS:
            {
                if(duty[1]==8000)
                {
                    duty[1]=2000;
                    pwm_duty(PWM2P_P22, 5000);//反转时先刹车
                    delay_ms(200);
                }
                else
                    duty[1]+=100;
                pwm_duty(PWM2P_P22, duty[1]);
                break;
            }
            case KEY2_PRESS:
            {
                if(duty[2]==8000)
                {
                    duty[2]=2000;
                    pwm_duty(PWM3P_P24, 5000);//反转时先刹车
                    delay_ms(200);
                }
                else
                    duty[2]+=1000;
                pwm_duty(PWM3P_P24, duty[2]);
                break;
            }
            case KEY3_PRESS:
            {
                if(duty[3]==8000)
                {
                    duty[3]=2000;
                    pwm_duty(PWM4P_P26, 5000);//反转时先刹车
                    delay_ms(200);
                }
                else
                    duty[3]+=1000;
                pwm_duty(PWM4P_P26, duty[3]);
                
                
                if(duty[4]==900)
                {
                    duty[4]=700;
                    pwm_duty(PWM7_P33,  800);//反转时先归中
                    delay_ms(200);
                }
                else
                    duty[4]+=25;
                pwm_duty(PWM7_P33, duty[4]);
                break;
            }
            default:break;
        }
        
    }
}

