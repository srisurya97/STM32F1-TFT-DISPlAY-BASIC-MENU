#include "spi.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
//#include "stm32f10x_rcc.h"
//#include "stm32f10x_usart.h"
//#include "usart.h"

                         /////////////////Initilizing ports for SPI with TFT/////////////////
void SPI1_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
		SPI_InitTypeDef  SPI_InitStructure;
  
		RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;										   //Enabling Clock for PORTA
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;									  	 //Enabling Clock for PORTB
		RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;										   //Enabling Clock for AFIO
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;										   //Enabling Clock for SPI1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;	 //Enabling Pin_5 for sck | pin7 for MOSI
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  				 //Output mode Alternate PushPull  
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;				 //Speed 50MHz
		GPIO_Init(GPIOA, &GPIO_InitStructure);									 //Configuring with above settings
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;  							 //Enabling Pin_4 PortA
   	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			 //Speed 50MHz
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				 //Output mode General PushPull  	
	  GPIO_Init(GPIOA, &GPIO_InitStructure);									 //Configuring with above settings
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);											 //Configure PA4 for LCD_CS. Defined in lcd.h for LCD_CS 

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;  							 //Enabling Pin_1  PortB
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			 //Speed 50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				 //Output mode General PushPull  		
    GPIO_Init(GPIOB, &GPIO_InitStructure); 									 //Configuring with above settings
		GPIO_ResetBits(GPIOB, GPIO_Pin_1);											 //Configure PA1 for LCD_DC. Defined in lcd.h for LCD_DC

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;							   //Enabling Pin_0  PortB
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			 //Speed 50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 				 //Output mode General PushPull  		
    GPIO_Init(GPIOB, &GPIO_InitStructure);									 //Configuring with above settings
		GPIO_ResetBits(GPIOB, GPIO_Pin_0);											 //Configure PB0 for LCD_RST. Defined in lcd.h for LCD_RST


													/////////////////Initilizing ports the SPI1 for Display/////////////////
 
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //SPI_Direction_1Line_Tx
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;												//SPI Master Mode
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;										//SPI Data SIze 8Bit
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;													//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;												//���ݲ����ڵڶ���ʱ����
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;														//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI_InitStructure.SPI_BaudRatePrescaler =SPI_BaudRatePrescaler_2;		//SPI setting for 36MHz 
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;									//Setting for firstBit as MSB
		SPI_InitStructure.SPI_CRCPolynomial = 7;														//CRC
		SPI_Init(SPI1, &SPI_InitStructure);  																//Configuring with above settings
 
		SPI_Cmd(SPI1, ENABLE); 																							//SPI1 Enabled
	
		/*	SPI_BaudRatePrescaler_2      (SPI 36M@sys 72M)
				SPI_BaudRatePrescaler_8      (SPI 9M@sys 72M)
				SPI_BaudRatePrescaler_16     (SPI 4.5M@sys 72M)
				SPI_BaudRatePrescaler_256    (SPI 281.25K@sys 72M)  */
	
	}
	
	
	uint8_t SPI_WriteByte(SPI_TypeDef* SPIx,uint8_t Byte)
	{
		while((SPIx->SR&SPI_I2S_FLAG_TXE)==RESET);		
		SPIx->DR=Byte; 
		while((SPIx->SR&SPI_I2S_FLAG_RXNE)==RESET);
		return SPIx->DR;          	   
	}

										/////////////////Initilizing ports the SPI2 for Touch/////////////////
/*
void SPI2_Init(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
  	SPI_InitTypeDef  SPI_InitStructure;
		//RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTBʱ��ʹ�� 
		RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );//SPI2ʱ��ʹ�� 	
 
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15����������� 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  //PB13/14/15����

		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
		SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//����SPI����ģʽ:����Ϊ��SPI
		SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
		SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;		//ѡ���˴���ʱ�ӵ���̬:ʱ�����ո�
		SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;	//���ݲ����ڵڶ���ʱ����
		SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
		SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;		//���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
		SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
		SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRCֵ����Ķ���ʽ
		SPI_Init(SPI2, &SPI_InitStructure);  //����SPI_InitStruct��ָ���Ĳ�����ʼ������SPIx�Ĵ���
 
		SPI_Cmd(SPI2, ENABLE); //ʹ��SPI����
	
		SPI2_ReadWriteByte(0xff);//��������	 

	}   
	//SPI �ٶ����ú���
	//SpeedSet:
	//SPI_BaudRatePrescaler_2   2��Ƶ   (SPI 36M@sys 72M)
	//SPI_BaudRatePrescaler_8   8��Ƶ   (SPI 9M@sys 72M)
	//SPI_BaudRatePrescaler_16  16��Ƶ  (SPI 4.5M@sys 72M)
	//SPI_BaudRatePrescaler_256 256��Ƶ (SPI 281.25K@sys 72M)
  

                	
void SPI2_SetSpeed(uint8_t SpeedSet)
	{
		SPI2->CR1&=0XFFC7; 
		SPI2->CR1|=SpeedSet;
		SPI_Cmd(SPI2,ENABLE); 
	} 

	//SPIx ��дһ���ֽ�
	//TxData:Ҫд����ֽ�
	//����ֵ:��ȡ�����ֽ�
uint8_t SPI2_ReadWriteByte(uint8_t TxData)
	{
		uint8_t retry=0;				 	
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)			//���ָ����SPI��־λ�������:���ͻ���ձ�־λ
			{
				retry++;
				if(retry>200)return 0;
			}			  
		SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
		retry=0;

		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
			{
				retry++;
				if(retry>200)return 0;
			}	  						    
		return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
	}          */
	





