#include "stm32f4xx.h"

int main(void){

    //-------------------UART----------------------//

    //USART2にクロックを供給
    RCC->APB1ENR |= 1 << 17;

    //Baudrateを設定
    uint32_t BaudRate = 115200;
    USART2->BRR = 16000000 / BaudRate;

	//GPIOAにクロックを供給
    RCC->AHB1ENR |= 0x01;

    //PA2とPA3にAlternateモードに設定
    GPIOA->MODER |= 0b10 << 4;
    GPIOA->MODER |= 0b10 << 6;

    //PA2とPA3をUSART2に設定(AF7)
    GPIOA->AFR[0] |= 0b0111 << 8;
    GPIOA->AFR[0] |= 0b0111 << 12;

    //PA2とPA3にPullUpを設定
    GPIOA->PUPDR |= 0b01 << 4;
    GPIOA->PUPDR |= 0b01 << 6;

    //USART2RxとTxを有効化
    USART2->CR1 |= 0b11 << 2;

    //USART2を有効化
    USART2->CR1 |= 1 << 13;

    while(1){

    	//1文字目
    	while(!(USART2->SR & 0x80));

    	USART2->DR = 97;

    	while(!(USART2->SR & 0x40));

    	//改行コード
    	while(!(USART2->SR & 0x80));

    	USART2->DR = 10;

    	while(!(USART2->SR & 0x40));

    	for(volatile uint32_t i=0;i<1000000;i++);
    }
    return 0;
}
