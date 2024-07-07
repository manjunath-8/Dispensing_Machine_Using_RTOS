#include <lpc17xx.h>
#include "Lcd.h"

void lcd_init()
{
  LPC_PINCON->PINSEL3 &= 0xFFFF00FF;  //P1.20 to P1.23
	LPC_PINCON->PINSEL7 &= 0XFFF3FFFF;  //P3.25
  LPC_PINCON->PINSEL7 &= 0xFFCFFFFF;  //P3.26
	LPC_PINCON->PINSEL9 &= 0xFCFFFFFF;  //P4.28

  LPC_GPIO1->FIODIR |= DT_CTRL;	// data lines - P1.20 to P1.23
	LPC_GPIO3->FIODIR |= RS_CTRL;	// RS - P3.25
  LPC_GPIO3->FIODIR |= RW_CTRL;	// RW - P3.26
	LPC_GPIO4->FIODIR |= EN_CTRL;	// P4.28 
        
  clear_ports();
	delay_lcd(3200);
	temp1 = 0x30;
	lcd_com();
	delay_lcd(30000);
	
	temp1 = 0x30;
	lcd_com();
	delay_lcd(30000);
	
	temp1 = 0x20;
	lcd_com();
	delay_lcd(30000);
	
	temp1 = 0x20;
	lcd_com();
	delay_lcd(30000);

	temp1 = 0x28;
	lcd_com();
	delay_lcd(30000);
		
	temp1 = 0x06;		
	lcd_com();
	delay_lcd(30000);
	
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(30000);
	
	temp1 = 0x0e;
	lcd_com();
	delay_lcd(30000);
	return;
}

void lcd_com()
{
	temp2= temp1 & 0xf0;
	temp2 = temp2 << 16;				//data lines from 20 to 23
	wr_cn();
	temp2 = temp1 & 0x0f;
	temp2 = temp2 << 20; 
	wr_cn();
	delay_lcd(1000);
  return;
}

void wr_cn(void)                        //write command reg
{ 	 
	clear_ports();
	LPC_GPIO1->FIOPIN = temp2;		// Assign the value to the data lines    
	LPC_GPIO3->FIOCLR = RW_CTRL;		// clear bit RW
  LPC_GPIO3->FIOCLR = RS_CTRL;		// clear bit RW
	LPC_GPIO4->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO4->FIOCLR  = EN_CTRL;		 		// EN =0
    return; 
 }

 void lcd_data(void)
{
    temp2 = temp1 & 0xf0;
    temp2 = temp2 << 16;
    wr_dn();
    temp2 = temp1 & 0x0f;
    temp2 = temp2 << 20;
    wr_dn();
    delay_lcd(1000);
    return;
}

void wr_dn(void)
{  	  
	clear_ports();

	LPC_GPIO1->FIOPIN = temp2;			// Assign the value to the data lines    
	LPC_GPIO3->FIOSET = RS_CTRL;		// set bit  RS
	LPC_GPIO3->FIOCLR = RW_CTRL;		// clear bit  RW
	LPC_GPIO4->FIOSET = EN_CTRL;   	// EN=1
	delay_lcd(25);
	LPC_GPIO4->FIOCLR  = EN_CTRL;	// EN =0
    return;
 }

void delay_lcd(unsigned int r1)
{
  	unsigned int r;
  	for(r=0;r<r1;r++);
    return;
}

void clr_disp(void)
{
	temp1 = 0x01;
	lcd_com();
 	delay_lcd(10000);
    return;
}
void clear_ports(void)
{
	LPC_GPIO1->FIOCLR = DT_CTRL; //Clearing data lines
	LPC_GPIO3->FIOCLR = RS_CTRL;  //Clearing RS line
  LPC_GPIO3->FIOCLR = RW_CTRL;  //Clearing RW line
	LPC_GPIO4->FIOCLR = EN_CTRL; //Clearing Enable line
        
    return;
}

void lcd_puts(unsigned char *buf1)
{
    unsigned int i=0;

    while(buf1[i]!='\0')
    {
        temp1 = buf1[i];
       	lcd_data();
	   	  i++;
    }
        return; 
}
