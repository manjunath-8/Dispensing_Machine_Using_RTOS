#include <lpc17xx.h>
#include "Lcd.h"
#include "uart.h"

unsigned char receive();
void transmit(unsigned char ch);
void delay(unsigned int x);
void complete(unsigned char mg,unsigned char C);

unsigned long int temp1=0, temp2=0 ;
unsigned char Msg1[14] = {"A     B     C"};
unsigned char Msg2[15] = {"100   40    10"};

void dispense() 
{ 
unsigned char success[]="Please enter the name of item and no.of items here---->"; 
unsigned int i;
unsigned char mg,C;  
while(1)
{ 
for(i=0;success[i]!='\0';i++)
{ 
transmit(success[i]); 
} 
mg=receive();
transmit(mg);
C=receive();
transmit(C);
if(mg=='A')
{ 
LPC_GPIO1->FIOSET = 0x06000000; 
LPC_GPIO1->FIOCLR = 0x02000000;
delay(500000000);
LPC_GPIO1->FIOCLR = 0x04000000;
complete(mg,C);
} 
else if(mg=='B') 
{ 
LPC_GPIO1->FIOSET = 0x00000100; 
LPC_GPIO1->FIOCLR = 0x00000200;
delay(50000000);
LPC_GPIO1->FIOCLR = 0x00000300;
complete(mg,C);
complete(mg,C); }
else if(mg=='C')
{ 
LPC_GPIO1->FIOSET = 0x00000200; 
LPC_GPIO1->FIOCLR = 0x00000100;
delay(25000000);
LPC_GPIO1->FIOSET = 0x00000200; 
LPC_GPIO1->FIOCLR = 0x00000100;
delay(50000000);
LPC_GPIO1->FIOCLR = 0x00000300;
complete(mg,C); 
} 
else
{ 
LPC_GPIO1->FIOCLR = 0x00000300;
}
}
}

void delay(unsigned int x)
{ 
int i; 
for(i=0;i<x;i++); 
}

void complete(unsigned char mg,unsigned char C) 
{
int i,k,l=0;
unsigned char a[5]; 
unsigned char cmp[]="Amount---->";
transmit(0X0D);
transmit(0x0A); 
for(i=0;cmp[i]!='\0';i++)
{ 
transmit(cmp[i]); 
}
k=(C-'0'); // total amount multiplication
if(mg=='A') 
k=k*100;
if(mg=='B') 
k=k*40;
if(mg=='C') 
k=k*10;
i=0;
while(k)
{ 
a[i]=((k%10)+'0'); 
k=k/10;
i++; l++;
}
for(i=l-1;i>=0;i--)
{ 
transmit(a[i]); 
}
transmit(0X0D);
transmit(0x0A);
while(1) 
{ 
dispense();
} 
}

unsigned char receive() 
{ 
while(!(LPC_UART0->LSR & 0x01));
return(LPC_UART0->RBR); 
} 
void transmit(unsigned char ch)
{ 
while(!(LPC_UART0->LSR & 0x20));
LPC_UART0->THR = ch;
}


int main(void)
{
	LPC_GPIO1->FIODIR = 0x06000000;
	LPC_GPIO1->FIOCLR = 0x06000000;
	SystemInit();
	SystemCoreClockUpdate();
   
  lcd_init();
	UART0_Init();
	delay_lcd(3200);

	temp1 = 0x80;			//1st message on LCD 1st line
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg1);
	
	temp1 = 0xc0;			//2nd message on LCD 2nd line
	lcd_com();
	delay_lcd(800);
	lcd_puts(Msg2);
	
	dispense();
  return 0;	
}