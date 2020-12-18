#include "main.h"
#include "i2c.h"

#ifndef HTS221_H_
#define HTS221_H_
#endif /* HTS221_H_ */

#define		HTS221_DEVICE_ADDRESS					0x5F
#define		HTS221_DEVICE_ADDR_WRITE				0xBE
#define		HTS221_DEVICE_ADDR_READ					0xBF

#define 	HTS221_WHO_AM_I_VALUE					0xBC
#define 	HTS221_WHO_AM_I_ADDRESS					0x0F

#define 	HTS221_CTRL_REG1 						0x20
#define 	HTS221_CTRL_REG1_VAL					0x81

#define		HTS221_T1_T0_MSB						0x35
#define		HTS221_T0_degC_x8						0x32
#define		HTS221_T1_degC_x8						0x33
#define		HTS221_T_OUT							0x2A
#define		HTS221_T0_OUT							0x3C
#define		HTS221_T1_OUT							0x3E

// Vlhkost
#define		HTS221_H_OUT							0x28

#define		HTS221_H_0_RH							0x30
#define		HTS221_H_1_RH							0x31

#define		HTS221_H_0								0x36
#define		HTS221_H_1								0x3A



uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
float hts221_get_temp();
uint8_t hts221_get_humidity();
