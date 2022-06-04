#include <stm32f4xx.h>

void USART2_init(void){
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
