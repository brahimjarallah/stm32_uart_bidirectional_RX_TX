#include <stm32f4xx.h>
#include <stdio.h>

void USART2_Init(void);
int USART2_write(int ch);
	
int main(void){
	int n;
	char str[100];
	printf("Hello there !\n");
	fprintf(stdout,"test for stdout \r\n "); 
	fprintf(stderr,"test for stderr \r\n "); 
	while(1){
		printf("how old are you?");
		scanf("%d",&n);
		printf("your age is: %d\r\n",n);
		printf("Enter your first name:");
		gets(str);
		printf("I like your style: ");
		puts(str);
		printf("\r\n");
	}
}

void USART2_Init(void){
	RCC->AHB1ENR |= 0x1; //enable port A
	RCC->APB1ENR |= 0x20000; // enable USART22
	GPIOA->AFR[0] |= 0x7700; // enable alternate function register for USART2 RX & TX (PA2 & PA3 )
	GPIOA->MODER |= 0xA0; // enable alternate function for PA2 & PA3

	USART2-> BRR = 0x683; // BR = 9600 @ 16Mhz
	USART2->CR1 |= 0xC; // 	enable UART TX & RX
	USART2->CR1 |= 0x2000; // ENABLE UART MODULE
}

int USART2_write(int ch){
	while(USART2->SR & 0x80){  // while TX buffer is empty
		USART2->DR = (ch & 0xFF);
		return ch;
	}
	}

int USART2_read(void){
	while(USART2->SR & 0x20){  // while RX buffer is empty
		USART2->DR;
	}
}

struct __FILE{int handle;};
FILE __stdin = {0};
FILE __stdout = {1}; 
FILE __stderr = {2};

int fgetc(FILE *f){
	int c;
	c =USART_read();
	if(c == '\r'){
		USART_write(c);
		c='\n'; 
	} 
	USART2_write(c);
	return c; 
}

int fputs(int c, FILE *f){
	return USART2_write(c);  
}
