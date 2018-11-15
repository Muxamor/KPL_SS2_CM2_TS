
#include "stm32l4xx.h"
#include "stm32l4xx_ll_utils.h"
#include "stm32l4xx_ll_gpio.h"
#include "stm32l4xx_ll_usart.h"
//#include "stm32l4xx_ll_exti.h"
#include "SetupPeriph.h"

#include "uart_comm.h"


//#include "global_variables.h"

#include  <stdio.h>


ErrorStatus Data_transmite_UART_9B (uint16_t mass[], uint8_t size_parcel,  USART_TypeDef *USARTx){

	uint32_t counter=0;

	//Enable transmit data
	//Enable_transmit_USART1();
	LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_11); //Enable transmit data
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	__NOP();
	
	
	if(LL_USART_IsActiveFlag_ORE(USARTx) == 1){
		LL_USART_ClearFlag_ORE(USARTx);
	}

	if(LL_USART_IsActiveFlag_RXNE(USARTx) == 1){
		LL_USART_ReceiveData9(USARTx);
	}

	counter=0;
	while( LL_USART_IsActiveFlag_TXE(USARTx) == RESET ){
		counter++;
		if(counter==40000){
			Error_Handler();
			return ERROR;
		}
	}

	for ( uint8_t i=0 ; i<size_parcel; i++ ){

		counter=0;
		while( LL_USART_IsActiveFlag_TC( USARTx ) == RESET ){
			counter++;
			if(counter==40000){//150ms
				Error_Handler();
				Disable_transmit_USART1();
				return ERROR;
			}
		}

		if (i==0){
			LL_USART_TransmitData9( USARTx, 0x100 | mass[i] );//set 9 bit for command (first) bite 

		}else{
			LL_USART_TransmitData9( USARTx, mass[i] );

		}
	}

	counter=0;
	while( LL_USART_IsActiveFlag_TC( USARTx ) == RESET ){
		counter++;
		if(counter==40000){//150ms
			Error_Handler();
			Disable_transmit_USART1();
			return ERROR;
		}
	}


	//Disable transmit data
	__NOP();
	LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_11);
	//Disable_transmit_USART1();
	return SUCCESS;
}


/**
  * @brief  Receive data throught UARTx 4 bytes
  * @param  void
  * @retval head byte put MSB
  */
ErrorStatus  Data_receive_UART_9B (uint16_t receive_data[] , uint8_t size_rec_data , USART_TypeDef *USARTx){

	uint32_t counter=0;
	uint8_t i=0;

	/*if(LL_USART_IsActiveFlag_ORE(USARTx) == 1){
		LL_USART_ClearFlag_ORE(USARTx);
		LL_USART_ReceiveData9(USARTx);
	}*/

	for( i=0; i<size_rec_data; i++ ){
		counter=0;
		while( LL_USART_IsActiveFlag_RXNE(USARTx) == RESET ){
			counter++;
			if(counter == 100000){
				Error_Handler();
				LL_USART_ClearFlag_ORE(USARTx);
				return ERROR;
			}
		}

		receive_data[i] = LL_USART_ReceiveData9(USARTx);
	}

	return SUCCESS;
}


