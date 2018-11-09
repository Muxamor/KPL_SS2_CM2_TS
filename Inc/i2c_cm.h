

#ifndef __I2C_CM_H
#define __I2C_CM_H

#ifdef __cplusplus
 extern "C" {
#endif

 extern void _Error_Handler(char *, int);

// uint8_t I2C_Read_addr_a_module(I2C_TypeDef *I2Cx,uint32_t SlaveAddr);
 ErrorStatus I2C_write_reg_TCA9554(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint8_t value);

 ErrorStatus I2C_write_reg_8bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint8_t value);
 ErrorStatus I2C_write_reg_16bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg, uint16_t value);
 uint8_t I2C_read_reg_8bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg);
 uint16_t I2C_read_reg_16bit_TMP75(I2C_TypeDef *I2Cx , uint8_t SlaveAddr_IC, uint8_t addr_reg);


#ifdef __cplusplus
}
#endif


#endif /* __I2C_CM1_H */
