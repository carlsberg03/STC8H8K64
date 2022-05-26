/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：一群：179029047(已满)  二群：244861897(已满)  三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		apic(中断优先级管理)
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ790875685)
 * @version    		查看doc内version文件 版本说明
 * @Software 		MDK FOR C51 V9.60
 * @Target core		STC8H8K64x
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-4-14
 ********************************************************************************************************************/
#include "zf_nvic.h"

//-------------------------------------------------------------------------------------------------------------------
//  @brief      中断优先级管理
//  @param      irqn         选择IRQn模块
//  @param      priority     从0到3，优先级依次增加
//  @return     void
//  Sample usage:         	 NVIC_SetPriority(UART1_IRQn, 3);	//设置串口 1 中断优先级为 3 级（最高级）
//  @note					 如果在周期中断中，通过串口发送数据。
//							 那么串口中断的优先级一定要高于周期中断的优先级
//						 	 这样才能正常发送数据。	
//-------------------------------------------------------------------------------------------------------------------
void NVIC_SetPriority(NVIC_IRQn_enum irqn,uint8 priority)
{
	if((irqn >> 4) == 0)
	{
		IP  |= (priority & 0x01) << (irqn & 0x0F);
		IPH |= ((priority >> 1) & 0x01) << (irqn & 0x0F);
	}
	else if((irqn >> 4) == 1)
	{
		IP2  |= (priority & 0x01) << (irqn & 0x0F);
		IP2H |= ((priority >> 1) & 0x01) << (irqn & 0x0F);
	}
	else if((irqn >> 4) == 2)
	{
		IP3  |= (priority & 0x01) << (irqn & 0x0F);
		IP3H |= ((priority >> 1) & 0x01) << (irqn & 0x0F);
	}
}

