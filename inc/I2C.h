#ifndef __I2C_H__
#define __I2C_H__


void I2C_Master_Init(void);
void I2C_Master_Read_Data(unsigned char addr, unsigned char * receivedata, unsigned char receivelen);
void I2C_Master_Write_Data(unsigned char addr, unsigned char * senddata, unsigned char sendlen, unsigned char is_stop);
#endif
