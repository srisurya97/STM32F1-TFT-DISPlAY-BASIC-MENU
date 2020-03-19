#ifndef __LCD_H
#define __LCD_H		

#include "sys.h" 
#include "stdlib.h"
#include "stm32f10x.h"


// REdefine for LCD controls
//LCD_RST PortB_0
#define SPILCD_RST_SET  GPIO_SetBits(GPIOB, GPIO_Pin_0)     
#define SPILCD_RST_RESET GPIO_ResetBits(GPIOB, GPIO_Pin_0)
//LCD_RS/DC PortB_1  
#define SPILCD_RS_SET  GPIO_SetBits(GPIOB,  GPIO_Pin_1)
#define SPILCD_RS_RESET  GPIO_ResetBits(GPIOB, GPIO_Pin_1)
//LCD_CS  PortA_4
#define SPILCD_CS_SET GPIO_SetBits(GPIOA,GPIO_Pin_4 ) 
#define SPILCD_CS_RESET  GPIO_ResetBits(GPIOA, GPIO_Pin_4)

  
typedef struct  
{ 					    
	uint16_t width;			//LCD ���
	uint16_t height;			//LCD �߶�
	uint16_t id;				//LCD ID
	uint8_t	wramcmd;		//��ʼдgramָ��
	uint8_t  setxcmd;		//����x����ָ��
	uint8_t  setycmd;		//����y����ָ��	 
}_lcd_dev; 	  

//LCD����
extern _lcd_dev lcddev;	
extern uint16_t  POINT_COLOR;
extern uint16_t  BACK_COLOR; 

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
#define	LCD_REST PBout(1) //LCD REST    		 PB1 	    

typedef struct
{
	uint16_t LCD_REG;
	uint16_t LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E			    
#define LCD_BASE        ((uint32_t)(0x60000000 | 0x0007FFFE))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
//////////////////////////////////////////////////////////////////////////////////

//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 	 0x001F  
#define BRED             0XF81F
#define GRED	 					 0XFFE0
#define GBLUE						 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 		 0XBC40 //��ɫ
#define BRRED 			 	   0XFC07 //�غ�ɫ
#define GRAY  			 		 0X8430 //��ɫ
#define COBALT					 0xAA00FF	
#define INDIGO					 0xA20025
#define AMBER						 0x008A00
#define TEAL						 0x225
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 		 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)
	    															  
void LCD_Init(void);			
void LCD_DisplayOn(void);	
void LCD_DisplayOff(void);													
void LCD_Clear(uint16_t Color);	 												
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);							
void LCD_DrawPoint(uint16_t x,uint16_t y);										
void LCD_Fast_DrawPoint(uint16_t x,uint16_t y,uint16_t color);			
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r);								
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);	
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color);		
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color);
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode);			
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size);  			
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p);	
	  
void showimage(uint16_t x,uint16_t y); 
void LCD_WriteReg(uint8_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WR_DATA8(uint8_t da);   
 
void showhanzi16(unsigned int x,unsigned int y,unsigned char index);
void showhanzi32(unsigned int x,unsigned int y,unsigned char index);						  		 
#endif  
	 
	 



