
#ifndef __UART_COMM_H
#define __UART_COMM_H
#ifdef __cplusplus
 extern "C" {
#endif

 extern void _Error_Handler(char *, int);

ErrorStatus Data_transmite_UART_9B (uint16_t mass[], uint8_t size_parcel, USART_TypeDef *USARTx);
ErrorStatus  Data_receive_UART_9B (uint16_t receive_data[] , uint8_t size_rec_data , USART_TypeDef *USARTx);

#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */


