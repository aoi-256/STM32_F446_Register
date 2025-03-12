#include "stm32f4xx.h"

int main(void){

	//GPIOAにクロックを供給
    RCC->AHB1ENR |= 0x01;

    //PA5を"General purpose output mode"にする
    GPIOA->MODER |= 0b01 << 10;

    while(1){

    	  //Delay
        for(volatile uint32_t i=0;i<1000000;i++);

        //PA5をset
        GPIOA->BSRR |= 1 << 5;

        //Delay
        for(volatile uint32_t i=0;i<1000000;i++);

        //PA5をreset
        GPIOA->BSRR &= ~(1 << 5);//PA5のsetをクリア
        GPIOA->BSRR |= 1 << 21;//Resetに1を書き込み
    }
    return 0;
}

