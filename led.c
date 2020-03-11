#include "led.h"
#include "stm32f10x_gpio.h"
//#include "stm32f10x_rcc.h"
   
//��ʼ��PB5��PE5Ϊ�����.��ʹ���������ڵ�ʱ��		    
//LED IO��ʼ��
void LED_Init(void)
	{
		GPIO_InitTypeDef  GPIO_InitStructure;
 	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 // |RCC_APB2Periph_GPIOE

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;				 //LED0-->PB.5 	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
		GPIO_Init(GPIOA, &GPIO_InitStructure);					 //GPIOB.5
		GPIO_SetBits(GPIOA,GPIO_Pin_3);						 //PB.5 
 
	/*
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;	    		 //LED1-->PE.5 �˿�����, �������
		GPIO_Init(GPIOE, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
		GPIO_SetBits(GPIOE,GPIO_Pin_5); 						 //PE.5 ����� 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;	    		 //beep
		// GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
		GPIO_ResetBits(GPIOC,GPIO_Pin_12); 						 	  
		GPIO_SetBits(GPIOC,GPIO_Pin_12);   */
	}

 
