#include "24cxx.h" 
#include "zf_delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//24CXX���� ����(�ʺ�24C01~24C16,24C32~256δ��������!�д���֤!)		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////



//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	My_IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
uint8 AT24CXX_ReadOneByte(uint16 ReadAddr)
{				  
	uint8 temp=0;		  	    																 
    My_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		My_IIC_Send_Byte(0XA0);	   //����д����
		My_IIC_Wait_Ack();
		My_IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		My_IIC_Wait_Ack();		 
	}else My_IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	My_IIC_Wait_Ack(); 
    My_IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	My_IIC_Wait_Ack();	    
	My_IIC_Start();  	 	   
	My_IIC_Send_Byte(0XA1);           //�������ģʽ			   
	My_IIC_Wait_Ack();	 
    temp=My_IIC_Read_Byte(0);		   
    My_IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_WriteOneByte(uint16 WriteAddr,uint8 DataToWrite)
{				   	  	    																 
    My_IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		My_IIC_Send_Byte(0XA0);	    //����д����
		My_IIC_Wait_Ack();
		My_IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		My_IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	My_IIC_Wait_Ack();	   
    My_IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	My_IIC_Wait_Ack(); 	 										  		   
	My_IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	My_IIC_Wait_Ack();  		    	   
    My_IIC_Stop();//����һ��ֹͣ���� 
	delay_ms(10);	 
}
//��AT24CXX�����ָ����ַ��ʼд�볤��ΪLen������
//�ú�������д��16bit����32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
//Len        :Ҫд�����ݵĳ���2,4
void AT24CXX_WriteLenByte(uint16 WriteAddr,uint32 DataToWrite,uint8 Len)
{  	
	uint8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//��AT24CXX�����ָ����ַ��ʼ��������ΪLen������
//�ú������ڶ���16bit����32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
//Len        :Ҫ�������ݵĳ���2,4
uint32 AT24CXX_ReadLenByte(uint16 ReadAddr,uint8 Len)
{  	
	uint8 t;
	uint32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//���AT24CXX�Ƿ�����
//��������24XX�����һ����ַ(255)���洢��־��.
//���������24Cϵ��,�����ַҪ�޸�
//����1:���ʧ��
//����0:���ɹ�
uint8 AT24CXX_Check(void)
{
	uint8 temp;
	temp=AT24CXX_ReadOneByte(255);//����ÿ�ο�����дAT24CXX			   
	if(temp==0X55)return 0;		   
	else//�ų���һ�γ�ʼ�������
	{
		AT24CXX_WriteOneByte(255,0X55);
	    temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ ��24c02Ϊ0~255
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(uint16 ReadAddr,uint8 *pBuffer,uint16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ ��24c02Ϊ0~255
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(uint16 WriteAddr,uint8 *pBuffer,uint16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











