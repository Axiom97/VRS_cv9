#include "lps25hb.h"


uint8_t lps25hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, LPS25HB_DEVICE_ADDR_READ, 0));
}


void lps25hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, LPS25HB_DEVICE_ADDR_WRITE, 0);
}


void lps25hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, LPS25HB_DEVICE_ADDR_READ, 1);
}

float lps25hb_get_pressure(){
	uint8_t press_H=lps25hb_read_byte(LPS25HB_PRESS_OUT_H);
	uint8_t press_L=lps25hb_read_byte(LPS25HB_PRESS_OUT_L);
	uint8_t press_XL=lps25hb_read_byte(LPS25HB_PRESS_OUT_XL);

	uint32_t pressure=(press_H << 16) | (press_L << 8) | press_XL;
	float pressure_out= ((float)pressure)/(float)4096;


	return pressure_out;
}

uint8_t lps25hb_init(void)
{

	uint8_t status = 1;

	LL_mDelay(100);

	uint8_t val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRESS);

	if(val == LPS25HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		val = lps25hb_read_byte(LPS25HB_WHO_AM_I_ADDRESS);
		if(val == LPS25HB_WHO_AM_I_VALUE)
		{
			status = 1;
		}
		else
		{
			status = 0;
			//return status;
		}
	}

	//temp device init


	lps25hb_write_byte(LPS25HB_CTRL_REG1, LPS25HB_CTRL_REG1_VAL); 	// zapnutie  senzora a nastavenia

	return status;
}
