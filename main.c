#include <stm32f4xx.h>

void USART_init(void){
	RCC->AHB1ENR |= 0x1; //enable port A
	RCC->APB1ENR |= 0x200; // enable USART RX

}
