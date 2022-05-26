/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,�1�7�1�7�0�2�0�8�1�7
 * All rights reserved.
 * �1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7QQ�0�5�1�7�1�7�0�5�0�5�1�7�1�7179029047(�1�7�1�7�1�7�1�7)  �1�7�1�7�0�5�1�7�1�7244861897(�1�7�1�7�1�7�1�7)  �1�7�1�7�0�5�1�7�1�7824575535
 *
 * �1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�8�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7�0�2�0�8�1�7�1�7�1�7�1�7���1�7�Ą1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�9�1�7�1�7�0�2�1�7�1�7
 * �1�7�1�7�0�5�1�7�1�7�ˁ0�0�1�7���1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�0�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�7�1�7�0�0�1�7�1�7�1�7�1�7�0�2�0�8�1�7�1�7�0�2�1�7�0�7�1�7�1�7�1�7�1�7�1�7�1�7
 *
 * @file       		main
 * @company	   		�1�7�0�3�1�7�1�7�1�7�0�2�0�8�1�7�1�7�1�7�1�7�1�1�1�7�0�4
 * @author     		�1�7�1�7�0�2�0�8�1�7(QQ790875685)
 * @version    		�1�7�5�1doc�1�7�1�7version�1�7�0�4�1�7 �1�7�ځ0�5�1�7�1�7
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
uint16 duty;

uint8 key_scan(void)
{
    if((KEY0==0)||(KEY1==0)||(KEY2==0)||(KEY3==0))
	{
		delay_ms(10);//�0�4�1�7�1�7�1�7�1�7 
		if(KEY0==0)
		{
			while(!KEY0)
				;
			return KEY0_PRESS;
		}
		if(KEY1==0)
		{
			while(!KEY1)
				;
			return KEY1_PRESS;
		}
        if(KEY2==0)
		{
			while(!KEY2)
				;
			return KEY2_PRESS;
		}
        if(KEY3==0)
		{
			while(!KEY3)
				;
			return KEY3_PRESS;
		}
	} 	     
	return 0;// �1�7�1�2�1�7�1�7�1�7�1�7�1�7�1�7�1�7
}

void delay(uint16 duty)
{
	uint16 i=10000;
	while(--i);
	{
		if(i<duty) LED0=1;
					else LED0=0;
	}
	   
}
//board.h�1�7�0�4�1�7�1�7�1�7FOSC�1�7�1�7�0�5�1�7�1�7�1�7�1�7�0�20,�1�7�1�7�1�7�1�7�1�7�1�7�0�8�1�7�0�7�1�7�1�7�0�3�0�1�0�1�1�7�1�7

/*board.h�1�7�0�4�1�7�1�7�1�7FOSC�1�7�1�7�0�5�1�7�1�7�1�7���1�7�0�20�1�7�1�7�1�7�1�7�0�3�0�1�0�1�1�7�1�7�0�2FOSC�1�7�1�7�0�5�1�7�1�7
�1�7�1�7�0�0�1�7�1�7stc-isp�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�1�1�7�1�7�1�7�1�7�0�2�1�7�1�7�1�7�1�7�0�8�1�7�1�7IRC�0�1�1�7�1�7�1�7�1�7�1�7�1�7�0�2FOSC�1�7�1�7�0�5*/

/*�1�7�1�7board_init�1�7�1�7,�1�7�0�4�1�7�1�7�1�7P54�1�7�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�2�1�7�1�7�˄1�7�1�7
�1�7�1�7�1�7�1�7�1�7�0�8�0�0�1�7�1�7P54�1�7�1�7�1�7�1�7,�1�7�1�7�1�7�1�7�1�7�1�7board.c�1�7�0�4�1�7�1�7�ք1�7board_init()�1�7�1�7�1�7�1�7�1�7�1�7�0�1�1�7�1�7SET_P54_RESRT�1�7�1�7�1�7�1�7*/

void main()
{

	DisableGlobalIRQ();		//�1�7�1�9�1�7�1�7�1�7�1�7�؄1�7
	board_init();			//�1�7�1�7�0�3�1�7�1�7�1�7�1�8�1�7�1�7�0�6�1�7�1�7�1�7�1�7�1�7�1�7�1�7�0�1�1�7�1�7�1�7�0�4�1�7�1�7�1�7�0�6
  P1M0=P1M0|0x02;//P11 pull-up out
  BEEP=1;
  delay_ms(200);
  BEEP=0;
	//�1�7�0�4�1�7�1�7�1�7�Մ1�7�0�4�1�7�1�7�1�7�1�7�1�7(�1�7�1�7�1�7�Ǆ1�7�1�7�1�7�1�7�1�7�0�3�1�7�1�7�1�7�1�7�1�7�1�7�1�7)
duty=0;
    
	EnableGlobalIRQ();		//�1�7�1�7�1�7�1�7�1�7�1�7�1�7�؄1�7
    while(1)
	{

		 //�1�7�0�4�1�7�1�7�1�7�Մ1�7�1�7�0�8�0�7�1�7�1�7�0�4�1�7�ց0�6�1�7�1�7�1�7
		switch(key_scan())
        {
            case KEY0_PRESS:
            {
							duty+=100;
            }
						case KEY1_PRESS:
            {
							duty-=100;
            }
            default:break;
        }
		delay(duty);
   }
	
}
