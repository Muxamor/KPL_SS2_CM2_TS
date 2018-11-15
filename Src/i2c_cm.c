/*
 * i2c.c
 *
 *  Created on: Jul 10, 2018
 *      Author: muxamor
 */

#include "stm32l4xx.h"
#include "SetupPeriph.h"
#include "stm32l4xx_ll_i2c.h"
#include "i2c_cm.h"

#include  <stdio.h>


/**
  * @brief  Wriete register in TCA9554PWR
  * @param  I2C_TypeDef *I2Cx  -- Number port I2C
  			SlaveAddr_IC - Address Slave IC on bus I2C
  			addr_reg - Address registr TCA9554PWR
  			value - value to write to registry
  * @retval An ErrorStatus enumeration
  *          - SUCCESS: 
  *          - ERROR:   Not applicable
  */

ErrorStatus I2C_write_reg_TCA9554(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint8_t value){

	SlaveAddr_IC = SlaveAddr_IC<<1;

	uint32_t counter = 0;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx) == SET){
		counter++;
		if( counter == 25000 ) {//
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC,LL_I2C_ADDRSLAVE_7BIT, 2,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE ); //LL_I2C_GENERATE_START_READ
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, addr_reg);

	counter=0;
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET){
		counter++;
		if( counter == 25000 ){
			LL_I2C_ClearFlag_TXE(I2Cx);
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_TransmitData8(I2Cx, value);
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	while(LL_I2C_IsActiveFlag_STOP(I2Cx)==RESET);

	LL_I2C_ClearFlag_STOP(I2Cx);
	return SUCCESS;
}


ErrorStatus I2C_write_reg_8bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint8_t value){

	SlaveAddr_IC = SlaveAddr_IC<<1;

	uint32_t counter = 0;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx)==SET){
		counter++;
		if( counter == 25000 ){//aproximate 150ms
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC,LL_I2C_ADDRSLAVE_7BIT, 2,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE ); //LL_I2C_GENERATE_START_READ
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, addr_reg);

	counter=0;
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET){
		counter++;
		if( counter == 25000 ){//aproximate 150ms
			LL_I2C_ClearFlag_TXE(I2Cx);
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_TransmitData8(I2Cx, value);
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	while(LL_I2C_IsActiveFlag_STOP(I2Cx)==RESET);

	LL_I2C_ClearFlag_STOP(I2Cx);
	return SUCCESS;
}


ErrorStatus I2C_write_reg_16bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint16_t value){

	SlaveAddr_IC = SlaveAddr_IC<<1;

	uint32_t counter = 0;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx)==SET){
		counter++;
		if( counter == 25000 ){//aproximate 150ms
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC,LL_I2C_ADDRSLAVE_7BIT, 3,LL_I2C_MODE_AUTOEND,LL_I2C_GENERATE_START_WRITE ); //LL_I2C_GENERATE_START_READ
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, addr_reg);

	counter=0;
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET){
		counter++;
		if( counter == 25000){//aproximate 150ms
			LL_I2C_ClearFlag_TXE(I2Cx);
			Error_Handler();
			return ERROR;
		}
	}

	LL_I2C_TransmitData8(I2Cx, (uint8_t)(value>>8)); //byte1
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, (uint8_t) value ); //byte2
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	while(LL_I2C_IsActiveFlag_STOP(I2Cx)==RESET);

	LL_I2C_ClearFlag_STOP(I2Cx);
	return SUCCESS;

}

uint8_t I2C_read_reg_8bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg){

	uint8_t read_data;

	SlaveAddr_IC = SlaveAddr_IC<<1;

	uint32_t counter = 0;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx)==SET){
		counter++;
		if( counter == 25000){//aproximate 150ms
			Error_Handler();
			return 0xFF;
		}
	}

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC,LL_I2C_ADDRSLAVE_7BIT, 1,LL_I2C_MODE_SOFTEND,LL_I2C_GENERATE_START_WRITE ); //LL_I2C_GENERATE_START_READ
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, addr_reg);

	counter=0;
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET){
		counter++;
		if( counter == 25000){//aproximate 150ms
			LL_I2C_ClearFlag_TXE(I2Cx);
			Error_Handler();
			return 0xFF;
		}
	}
	while(LL_I2C_IsActiveFlag_TC(I2Cx)==RESET);

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ); //LL_I2C_MODE_SOFTEND

	while(LL_I2C_IsActiveFlag_RXNE(I2Cx)==RESET);

	read_data = LL_I2C_ReceiveData8(I2Cx);

	while(LL_I2C_IsActiveFlag_STOP(I2Cx)==RESET);
	LL_I2C_ClearFlag_STOP(I2Cx);

	return read_data;
}

uint16_t I2C_read_reg_16bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg){

	uint8_t read_data[2], i=0;

	SlaveAddr_IC = SlaveAddr_IC<<1;

	uint32_t counter = 0;
	while(LL_I2C_IsActiveFlag_BUSY(I2Cx)==SET){
		counter++;
		if( counter == 25000 ){//aproximate 150ms
			Error_Handler();
			return 0xFF;
		}
	}

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC,LL_I2C_ADDRSLAVE_7BIT, 1,LL_I2C_MODE_SOFTEND,LL_I2C_GENERATE_START_WRITE ); //LL_I2C_GENERATE_START_READ
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET);

	LL_I2C_TransmitData8(I2Cx, addr_reg);

	counter=0;
	while(LL_I2C_IsActiveFlag_TXE(I2Cx)==RESET){
		counter++;
		if( counter == 25000 ){//aproximate 150ms
			LL_I2C_ClearFlag_TXE(I2Cx);
			Error_Handler();
			return 0xFF;
		}
	}
	while(LL_I2C_IsActiveFlag_TC(I2Cx)==RESET);

	LL_I2C_HandleTransfer(I2Cx, SlaveAddr_IC, LL_I2C_ADDRSLAVE_7BIT, 2, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ); //LL_I2C_MODE_SOFTEND

	while(!LL_I2C_IsActiveFlag_STOP(I2Cx)){

		if(LL_I2C_IsActiveFlag_RXNE(I2Cx)){
			read_data[i] = LL_I2C_ReceiveData8(I2Cx);
			i++;
		}
	}

	LL_I2C_ClearFlag_STOP(I2Cx);

	return (read_data[0]<<8) | read_data[1];
}
