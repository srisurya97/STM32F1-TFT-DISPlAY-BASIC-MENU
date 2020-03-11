#include "lcd.h"
#include "stdlib.h"
#include "font.h" 
#include "delay.h"	   
#include "spi.h"	
#include "stm32f10x.h"
#include "stm32f10x_spi.h"
//#include "usart.h"	  				 
				 
				 
//LCD�Ļ�����ɫ�ͱ���ɫ	   
uint16_t POINT_COLOR=0x0000;	//������ɫ
uint16_t BACK_COLOR=0xFFFF;  //����ɫ 

//����LCD��Ҫ����
_lcd_dev lcddev;
	
		   
//д�Ĵ�������
//regval:�Ĵ���ֵ
void LCD_WR_REG(uint16_t regval)
	{
		SPILCD_CS_RESET;  //LCD_CS=0
    SPILCD_RS_RESET;
		SPI_WriteByte(SPI1,regval&0x00FF);
		SPILCD_CS_SET;  //LCD_CS=1	   		 
	}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(uint16_t data)
	{
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;	
		SPI_WriteByte(SPI1,data>>8);
		SPI_WriteByte(SPI1,data);
		SPILCD_CS_SET;  //LCD_CS=1		
	}

void LCD_WR_DATA8(uint8_t da)   
	{
		SPILCD_CS_RESET;  //LCD_CS=0
		SPILCD_RS_SET;				    	   
		SPI_WriteByte(SPI1,da);	
		SPILCD_CS_SET;  //LCD_CS=1   			 
	}					   
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������

void LCD_WR_REG_DATA(uint8_t LCD_Reg, uint16_t LCD_RegValue)
	{
		LCD_WR_REG(LCD_Reg);
		LCD_WR_DATA(LCD_RegValue);
	}
//��ʼдGRAM

void LCD_WriteRAM_Prepare(void)
	{
		LCD_WR_REG(lcddev.wramcmd);  
	}	 
//��mdk -O1ʱ���Ż�ʱ��Ҫ����
//��ʱi
	
void opt_delay(uint8_t i)
	{
		while(i--);
	}  		 
//LCD������ʾ

void LCD_DisplayOn(void)
	{					   

	}	 
//LCD�ر���ʾ

void LCD_DisplayOff(void)
	{	   

	}   

//���ù��λ��
//Xpos:������
//Ypos:������
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
	{
    LCD_WR_REG(lcddev.setxcmd); 
		LCD_WR_DATA8(Xpos>>8); 
		LCD_WR_DATA8(Xpos&0XFF);	 
		LCD_WR_REG(lcddev.setycmd); 
		LCD_WR_DATA8(Ypos>>8); 
		LCD_WR_DATA8(Ypos&0XFF);
	} 	  

//����
//x,y:����
//POINT_COLOR:�˵����ɫ

void LCD_DrawPoint(uint16_t x,uint16_t y)
	{
		LCD_SetCursor(x,y);
		LCD_WriteRAM_Prepare();	//��ʼд��GRAM
		LCD_WR_DATA(POINT_COLOR); 
	} 
//��ʼ��lcd

void LCD_Init(void)
	{ 	 	
		LCD_REST=0;		 
		delay_ms(50); // delay 20 ms 
   	LCD_REST=1;		 
		delay_ms(50); // delay 20 ms 

		SPILCD_RST_RESET ;	//LCD_RST=0	 //SPI�ӿڸ�λ
		delay_ms(20); // delay 20 ms 
    SPILCD_RST_SET ;	//LCD_RST=1		
		delay_ms(20);

		lcddev.width=240;
		lcddev.height=320;
		lcddev.wramcmd=0X2C;
		lcddev.setxcmd=0X2A;
		lcddev.setycmd=0X2B; 	

		LCD_WR_REG(0xCF);  
		LCD_WR_DATA8(0x00); 
		LCD_WR_DATA8(0xD9); 
		LCD_WR_DATA8(0X30); 
	 
		LCD_WR_REG(0xED);  
		LCD_WR_DATA8(0x64); 
		LCD_WR_DATA8(0x03); 
		LCD_WR_DATA8(0X12); 
		LCD_WR_DATA8(0X81); 
	 
		LCD_WR_REG(0xE8);  
		LCD_WR_DATA8(0x85); 
		LCD_WR_DATA8(0x10); 
		LCD_WR_DATA8(0x78); 
	 
		LCD_WR_REG(0xCB);  
		LCD_WR_DATA8(0x39); 
		LCD_WR_DATA8(0x2C); 
		LCD_WR_DATA8(0x00); 
		LCD_WR_DATA8(0x34); 
		LCD_WR_DATA8(0x02); 
	 
		LCD_WR_REG(0xF7);  
		LCD_WR_DATA8(0x20); 
	 
		LCD_WR_REG(0xEA);  
		LCD_WR_DATA8(0x00); 
		LCD_WR_DATA8(0x00); 
	 
		LCD_WR_REG(0xC0);    //Power control 
		LCD_WR_DATA8(0x21);   //VRH[5:0] 
	 
		LCD_WR_REG(0xC1);    //Power control 
		LCD_WR_DATA8(0x12);   //SAP[2:0];BT[3:0] 
	 
		LCD_WR_REG(0xC5);    //VCM control 
		LCD_WR_DATA8(0x32); 
		LCD_WR_DATA8(0x3C); 
	 
		LCD_WR_REG(0xC7);    //VCM control2 
		LCD_WR_DATA8(0XC1); 
	 
		LCD_WR_REG(0x36);    // Memory Access Control 
		LCD_WR_DATA8(0x08); 
	 
		LCD_WR_REG(0x3A);   
		LCD_WR_DATA8(0x55); 
	
		LCD_WR_REG(0xB1);   
		LCD_WR_DATA8(0x00);   
		LCD_WR_DATA8(0x18); 
	 
		LCD_WR_REG(0xB6);    // Display Function Control 
		LCD_WR_DATA8(0x0A); 
		LCD_WR_DATA8(0xA2); 
	
	 
	 
		LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
		LCD_WR_DATA8(0x00); 
	 
		LCD_WR_REG(0x26);    //Gamma curve selected 
		LCD_WR_DATA8(0x01); 
	 
		LCD_WR_REG(0xE0);    //Set Gamma 
		LCD_WR_DATA8(0x0F); 
		LCD_WR_DATA8(0x20); 
		LCD_WR_DATA8(0x1E); 
		LCD_WR_DATA8(0x09); 
		LCD_WR_DATA8(0x12); 
		LCD_WR_DATA8(0x0B); 
		LCD_WR_DATA8(0x50); 
		LCD_WR_DATA8(0XBA); 
		LCD_WR_DATA8(0x44); 
		LCD_WR_DATA8(0x09); 
		LCD_WR_DATA8(0x14); 
		LCD_WR_DATA8(0x05); 
		LCD_WR_DATA8(0x23); 
		LCD_WR_DATA8(0x21); 
		LCD_WR_DATA8(0x00); 
	 
		LCD_WR_REG(0XE1);    //Set Gamma 
		LCD_WR_DATA8(0x00); 
		LCD_WR_DATA8(0x19); 
		LCD_WR_DATA8(0x19); 
		LCD_WR_DATA8(0x00); 
		LCD_WR_DATA8(0x12); 
		LCD_WR_DATA8(0x07); 
		LCD_WR_DATA8(0x2D); 
		LCD_WR_DATA8(0x28); 
		LCD_WR_DATA8(0x3F); 
		LCD_WR_DATA8(0x02); 
		LCD_WR_DATA8(0x0A); 
		LCD_WR_DATA8(0x08); 
		LCD_WR_DATA8(0x25); 
		LCD_WR_DATA8(0x2D); 
		LCD_WR_DATA8(0x0F); 
	 
		LCD_WR_REG(0x11);    //Exit Sleep 
		delay_ms(120); 
		LCD_WR_REG(0x29);    //Display on 

		LCD_Clear(BLACK); 
	
	}  
//��������
//color:Ҫ���������ɫ

void LCD_Clear(uint16_t color)
	{
		uint32_t index=0;      
		uint32_t totalpoint=lcddev.width;
		totalpoint*=lcddev.height; 	//�õ��ܵ���
		LCD_SetCursor(0x00,0x0000);	//���ù��λ�� 
		LCD_WriteRAM_Prepare();     //��ʼд��GRAM	 	  
		for(index=0;index<totalpoint;index++)
		{
			LCD_WR_DATA(color);
		}

	}  
//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
	
void LCD_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t color)
	{          
		uint16_t i,j;
		uint16_t xlen=0;
		xlen=ex-sx+1;	   
		for(i=sy;i<=ey;i++)
		{									   
			LCD_SetCursor(sx,i);      				//���ù��λ�� 
			LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	  
			for(j=0;j<xlen;j++)LCD_WR_DATA(color);	//���ù��λ�� 	    
		}
	}  
//��ָ�����������ָ����ɫ��			 
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
	
void LCD_Color_Fill(uint16_t sx,uint16_t sy,uint16_t ex,uint16_t ey,uint16_t *color)
	{  
		uint16_t height,width;
		uint16_t i,j;
		width=ex-sx+1; 		
		height=ey-sy+1;		
		for(i=0;i<height;i++)
		{
			LCD_SetCursor(sx,sy+i);   	//���ù��λ�� 
			LCD_WriteRAM_Prepare();     //��ʼд��GRAM
			for(j=0;j<width;j++)LCD->LCD_RAM=color[i*height+j];//д������ 
		}	  
	}  
//����
//x1,y1:�������
//x2,y2:�յ�����  
	
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
	{
		uint16_t t; 
		int xerr=0,yerr=0,delta_x,delta_y,distance; 
		int incx,incy,uRow,uCol; 
		delta_x=x2-x1;
		delta_y=y2-y1; 
		uRow=x1; 
		uCol=y1; 
		if(delta_x>0)incx=1; 
		else if(delta_x==0)incx=0; 
		else {incx=-1;delta_x=-delta_x;} 
		if(delta_y>0)incy=1; 
		else if(delta_y==0)incy=0;
		else{incy=-1;delta_y=-delta_y;} 
		if( delta_x>delta_y)distance=delta_x; 
		else distance=delta_y; 
		for(t=0;t<=distance+1;t++ )
		{  
			LCD_DrawPoint(uRow,uCol);
			xerr+=delta_x ; 
			yerr+=delta_y ; 
			if(xerr>distance) 
				{ 
					xerr-=distance; 
					uRow+=incx; 
				} 
			if(yerr>distance) 
				{ 
					yerr-=distance; 
					uCol+=incy; 
				} 
		}  
	}    
//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
	
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
	{
		LCD_DrawLine(x1,y1,x2,y1);
		LCD_DrawLine(x1,y1,x1,y2);
		LCD_DrawLine(x1,y2,x2,y2);
		LCD_DrawLine(x2,y1,x2,y2);
	}
//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
	
void Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r)
	{
		int a,b;
		int di;
		a=0;b=r;	  
		di=3-(r<<1);             //�ж��¸���λ�õı�־
		while(a<=b)
			{
				LCD_DrawPoint(x0+a,y0-b);             //5
				LCD_DrawPoint(x0+b,y0-a);             //0           
				LCD_DrawPoint(x0+b,y0+a);             //4               
				LCD_DrawPoint(x0+a,y0+b);             //6 
				LCD_DrawPoint(x0-a,y0+b);             //1       
				LCD_DrawPoint(x0-b,y0+a);             
				LCD_DrawPoint(x0-a,y0-b);             //2             
				LCD_DrawPoint(x0-b,y0-a);             //7     	         
				a++;

			if(di<0)di +=4*a+6;	  
			else
				{
					di+=10+4*(a-b);   
					b--;
				} 						    
			}
	} 	
//��ָ��λ����ʾһ������(16*16��С)
	
void showhanzi16(unsigned int x,unsigned int y,unsigned char index)	
	{  
		unsigned char i,j,k;
		const unsigned char *temp=hanzi16;    
		temp+=index*32;	
		for(j=0;j<16;j++)
		{
			LCD_SetCursor(x,y+j);
			LCD_WriteRAM_Prepare();	//��ʼд��GRAM
			for(k=0;k<2;k++)
			{
				for(i=0;i<8;i++)
				{
					if((*temp&(1<<i))!=0)
						{
							LCD_WR_DATA(POINT_COLOR);
						}
						else
							{
								LCD_WR_DATA(BACK_COLOR);
							}   
				}
				temp++;
			}
		}
	}	
//��ָ��λ����ʾһ������(32*32��С)
	
void showhanzi32(unsigned int x,unsigned int y,unsigned char index)	
	{  
		unsigned char i,j,k;
		const unsigned char *temp=hanzi32;    
		temp+=index*128;	
		for(j=0;j<32;j++)
		{
			LCD_SetCursor(x,y+j);
			LCD_WriteRAM_Prepare();	//��ʼд��GRAM
			for(k=0;k<4;k++)
			{
				for(i=0;i<8;i++)
				{ 		     
					if((*temp&(1<<i))!=0)
						{
							LCD_WR_DATA(POINT_COLOR);
						}
						else
							{
								LCD_WR_DATA(BACK_COLOR);
							}   
				}
				temp++;
			}
		}
	}													  
//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)

void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode)
	{  							  
    uint8_t temp,t1,t;
		uint16_t y0=y;
		uint16_t colortemp=POINT_COLOR;      			     
	   
		num=num-' ';
		if(!mode) 
			{
				for(t=0;t<size;t++)
				{   
					if(size==12)temp=asc2_1206[num][t];  
					else temp=asc2_1608[num][t];		  	                          
	        for(t1=0;t1<8;t1++)
					{			    
		        if(temp&0x80)POINT_COLOR=colortemp;
						else POINT_COLOR=BACK_COLOR;
						LCD_DrawPoint(x,y);	
						temp<<=1;
						y++;
						if(y>=lcddev.height){POINT_COLOR=colortemp;return;}
						if((y-y0)==size)
							{
								y=y0;
								x++;
								if(x>=lcddev.width){POINT_COLOR=colortemp;return;}
								break;
							}
					}  	 
				}    
			}else
			{
				for(t=0;t<size;t++)
				{   
					if(size==12)temp=asc2_1206[num][t];  //����1206����
					else temp=asc2_1608[num][t];		 //����1608���� 	                          
	        for(t1=0;t1<8;t1++)
					{			    
		        if(temp&0x80)LCD_DrawPoint(x,y); 
						temp<<=1;
						y++;
						if(y>=lcddev.height){POINT_COLOR=colortemp;return;}//��������
						if((y-y0)==size)
							{
								y=y0;
								x++;
								if(x>=lcddev.width){POINT_COLOR=colortemp;return;}//��������
								break;
							}
					}  	 
				}     
			}
		POINT_COLOR=colortemp;	    	   	 	  
	}   

uint32_t LCD_Pow(uint8_t m,uint8_t n)
	{
		uint32_t result=1;	 
		while(n--)result*=m;    
		return result;
	}			 
//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 

void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size)
	{         	
		uint8_t t,temp;
		uint8_t enshow=0;						   
		for(t=0;t<len;t++)
		{
			temp=(num/LCD_Pow(10,len-t-1))%10;
			if(enshow==0&&t<(len-1))
				{
					if(temp==0)
						{
							LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
							continue;
						}else enshow=1; 
		 	 
				}
				LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
		}
	} 
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
	
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode)
	{  
		uint8_t t,temp;
		uint8_t enshow=0;						   
		for(t=0;t<len;t++)
		{
			temp=(num/LCD_Pow(10,len-t-1))%10;
			if(enshow==0&&t<(len-1))
				{
					if(temp==0)
						{
							if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
							else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
							continue;
						}else enshow=1; 
		 	 
				}
				LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
			}
	} 

	
void LCD_ShowString(uint16_t x,uint16_t y,uint16_t width,uint16_t height,uint8_t size,uint8_t *p)
	{         
		uint8_t x0=x;
		width+=x;
		height+=y;
    while((*p<='~')&&(*p>=' '))
			{       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;
        LCD_ShowChar(x,y,*p,size,1);
        x+=size/2;
        p++;
			}  
	}

void showimage(uint16_t x,uint16_t y) 
	{  
		uint16_t i,j,k;
		uint16_t da;
		k=0;
		for(i=0;i<40;i++)
		{	
			LCD_SetCursor(x,y+i);
			LCD_WriteRAM_Prepare();     			//��ʼд��GRAM	
			for(j=0;j<40;j++)
			{
				da=qqimage[k*2+1];
				da<<=8;
				da|=qqimage[k*2]; 
				LCD_WR_DATA(da);					
				k++;  			
			}
		}
	}





























