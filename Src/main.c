
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "SetupPeriph.h"
#include "i2c_cm.h"
#include "uart_comm.h"

#include  <stdio.h>


//LL_mDelay(1);
//LL_RCC_ClocksTypeDef check_RCC_Clocks,  *CHECK_RCC_CLOCKS=&check_RCC_Clocks; // Only for check setup clock. Not need use in release


int main(void){

	LL_Init();
	SystemClock_Config(); //Setup system clock at 80 MHz
	USART1_Init();
	I2C1_Init();
	IWDG_Init();

	//Default setup board and cross borad Address IC = 0x20, cross board.
	//Address IC TCA9554 = 0x20
 	I2C_write_reg_TCA9554(I2C1 , 0x20, 0x03, 0x00); // Set pin as output, Address IC = 0x20
	I2C_write_reg_TCA9554(I2C1 , 0x20, 0x01, 0xFF); // OFF all analog module in block, Address IC = 0x20
	//Address IC TCA9554 = 0x26
	I2C_write_reg_TCA9554(I2C1 , 0x26, 0x03, 0x00); // Set pin as output, Address IC = 0x26
	I2C_write_reg_TCA9554(I2C1 , 0x26, 0x01, 0xFF); // OFF all analog module in block, Address IC = 0x26
	////////////////////////////////////////


	//Default setup temperature senser TMP75
	uint8_t add_TMP75 = 0x49;
	for(/*empty*/; add_TMP75 < 0x4E; add_TMP75++){ // Setup all temperatura IC TMP75 Block 2

		I2C_write_reg_8bit_TMP75(I2C1, add_TMP75, 0x01, 0x00); //Configuration registr addr=0x01 TMP75: OS R1R0 F1F0 POL TM SD
													           // OS=0   R1R0 = 00 00   F1F0 = 00 00   POL = 00   TM = 00  SD = 00
		//Write Tlow registr addr=0x02 Tlow=30 in 12bit resolution = 0x1E0
		I2C_write_reg_16bit_TMP75(I2C1, add_TMP75, 0x02, (0x140 << 4) );

		//Write Thigh registr addr=0x03 Thigh=40 in 12bit resolution = 0x280
		I2C_write_reg_16bit_TMP75(I2C1, add_TMP75, 0x03, (0x190 << 4) );
	}

	uint16_t data_receive[4] = {0};
	uint16_t answer_array[4] = {0};
	uint8_t number_command = 0;
	ErrorStatus ret1, ret2;

	while(1){


		ret1 = Data_receive_UART_9B (data_receive, 4, USART1);
		LL_IWDG_ReloadCounter(IWDG);

		if( (ret1 == SUCCESS) && ( data_receive[0] == 0x0106 || data_receive[0] == 0x0107) ){

			number_command = (uint8_t)data_receive[0];

			answer_array[0] = data_receive[0] & 0x00FF;
			answer_array[1] = 0x0001;
			answer_array[2] = 0x0000;
			answer_array[3] = 0x0000;

			switch(number_command){

				case 0x06:

					if( ((uint8_t)data_receive[1]) == 0x00 ){

						ret1 = I2C_write_reg_TCA9554(I2C1, 0x20, 0x01, (~ ((uint8_t)data_receive[4]) ) ); // ON/OFF analog module in block1, Address IC = 0x20
						ret2 = I2C_write_reg_TCA9554(I2C1, 0x26, 0x01, (~ ((uint8_t)data_receive[3]) ) ); // ON/OFF analog module in block1, Address IC = 0x26

						if(ret1==ERROR || ret2==ERROR){
							answer_array[1] = 0x0000;
						}

					}else if( ((uint8_t)data_receive[1]) == 0x80 ){
						//TODO Answer
						answer_array[1] = 0x0000;
					}
					break;

				case 0x07:
					//TODO Control I2C temp sensor
					break;

				default:
					break;
			}

			LL_IWDG_ReloadCounter(IWDG);
			Data_transmite_UART_9B(answer_array, 4, USART1);
		}




	}

}

