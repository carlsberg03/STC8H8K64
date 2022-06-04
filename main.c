#include "headfile.h"
#define KEY0 P34
#define KEY1 P35
#define KEY2 P36
#define KEY3 P37
#define KEY0_PRESS 0
#define KEY1_PRESS 0
#define KEY2_PRESS 0
#define KEY3_PRESS 0
#define LED0 P70
#define LED1 P71
#define LED2 P72
#define LED3 P73
#define BEEP P11
uint16 adc_data[4];
uint16 adcdata;
uint16 duty[5];

float kp = 2;
int error;
int out;
	
int count=0;

void accelerate_left(int i)
{duty[0]=duty[0]+i;
 pwm_duty(PWM1P_P20, duty[0]);
}

void accelerate_right(int i)
{duty[1]=duty[1]+i;
 pwm_duty(PWM2P_P22, duty[1]);
}
void main()
{void accelerate_left(int i);
 void accelerate_right(int i);
	DisableGlobalIRQ();	//¹Ø±Õ×ÜÖÐ¶Ï
	board_init();	
	adc_init(ADC_P00, ADC_SYSclk_DIV_2);
	adc_init(ADC_P01, ADC_SYSclk_DIV_2);
    adc_init(ADC_P02, ADC_SYSclk_DIV_2);
	adc_init(ADC_P03, ADC_SYSclk_DIV_2);
	pwm_init(PWM7_P33, 50, 0);
    pwm_init(PWM1P_P20, 500, 6000);
    pwm_init(PWM2P_P22, 500, 6000);
    pwm_init(PWM3P_P24, 500, 6000);
    pwm_init(PWM4P_P26, 500, 6000);
    pwm_init(PWM1N_P21, 500, 3000);
    pwm_init(PWM2N_P23, 500, 3000);   
    pwm_init(PWM3N_P25, 500, 3000);
    pwm_init(PWM4N_P27, 500, 3000);
    duty[0]=7000;
    duty[1]=7000;
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
	EnableGlobalIRQ();
    while(1)
	{
		
		adc_data[0] = adc_once(ADC_P00, ADC_12BIT);
        oled_p6x8num(0,0,adc_data[0]);
        adc_data[1] = adc_once(ADC_P01, ADC_12BIT);
        oled_p6x8num(0,1,adc_data[1]);
        adc_data[2] = adc_once(ADC_P02, ADC_12BIT);
        oled_p6x8num(0,2,adc_data[2]);
        adc_data[3] = adc_once(ADC_P03, ADC_12BIT);
        oled_p6x8num(0,3,adc_data[3]);;
        oled_p6x8num(0,4,adcdata);
        adcdata=((adc_data[0]-adc_data[3])+(adc_data[1]-adc_data[2])+4000)/80;
				oled_p6x8num(0,5,duty[4]);
			/*
			  if(adcdata<=50)
				{duty[4]=830-3*(50-adcdata);
				 pwm_duty(PWM7_P33, duty[4]);
				}
				
	
				if(adcdata>50)
				{duty[4]=830+3*(adcdata-50);
				 pwm_duty(PWM7_P33, duty[4]);
				}
			
			*/
			error = adcdata - 50;
			out = (int) kp * error;
			if(out >= 140)
				out = 140;
			else if(out <= -100)
				out = -130;
			
			pwm_duty(PWM7_P33, (830 + out));
			
			/*
				//accelerate
				if(adcdata>3500&&adcdata<4500);
				{count++;
					if(count==10)
					{count=0;
					 accelerate_left(10);
					 accelerate_right(10);
					}
				}
				if(adcdata<3500||adcdata>4500)
					{
					count--;
					if(count==-10)
						{count=0;
						 accelerate_left(-10);
					   accelerate_right(-10);
					}
				}
				*/
	}
}

