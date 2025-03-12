#include "stm32f4xx.h"

/* @brief USART2の初期設定
 *
 * @param BaudRate	USARTの通信速度(bps)を設定
 *
 * @return None
 */
void USART2_Init(uint32_t BaudRate){

    //USART2にクロックを供給
    RCC->APB1ENR |= 1 << 17;

    //Baudrateを設定
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
}

/* @brief USART2の送信
 *
 * @param Data 送信データのポインタ
 * @param Len 　送信するデータ数
 *
 * @return None
 */
void USART2_Transmit(uint8_t* Data, uint8_t Len){

	//データを1byteずつ送信
	for(uint8_t i=0; i<Len; i++){

		//DRレジスタを待機
		while((USART2->SR & 0x80) == 0);

		USART2->DR = Data[i];

		//送信完了を待機
		while((USART2->SR & 0x40) == 0);
	}

	//改行コードを送る
	while((USART2->SR & 0x80) == 0);

	USART2->DR = 10;

	while((USART2->SR & 0x40) == 0);

}

int main(void){

	//初期設定
	USART2_Init(115200);

	//送信データ
	uint8_t SendData[255] = "abcdefg";

    while(1){

    	//データの送信
    	USART2_Transmit(SendData, 5);

    	//Delay
    	for(volatile uint32_t i=0;i<1000000;i++);

    }
    return 0;
}
