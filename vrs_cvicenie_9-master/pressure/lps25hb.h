#include "main.h"
#include "i2c.h"

#ifndef LPS25HB_H_
#define LPS25HB_H_
#endif /* LPS25HB_H_ */

#define		LPS25HB_DEVICE_ADDR_READ				0xBB
#define		LPS25HB_DEVICE_ADDR_WRITE				0xBA
#define		LPS25HB_STATUS							0x27
#define 	LPS25HB_WHO_AM_I_VALUE					0xBD
#define 	LPS25HB_WHO_AM_I_ADDRESS				0x0F

#define 	LPS25HB_CTRL_REG1						0x20
#define		LPS25HB_CTRL_REG1_VAL					0x90

#define		LPS25HB_PRESS_OUT_H						0x2A
#define		LPS25HB_PRESS_OUT_L						0x29
#define		LPS25HB_PRESS_OUT_XL					0x28



uint8_t lps25hb_init(void);
uint8_t lps25hb_read_byte(uint8_t reg_addr);
void lps25hb_write_byte(uint8_t reg_addr, uint8_t value);
void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
float lps25hb_get_pressure();
