#include "hts221.h"


uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, HTS221_DEVICE_ADDR_READ, 0));
}


void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, HTS221_DEVICE_ADDR_WRITE, 0);
}


void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, HTS221_DEVICE_ADDR_READ, 1);
}

uint8_t hts221_get_humidity(){
	uint8_t buffer[2];

	uint16_t h_0_rh=(uint16_t)hts221_read_byte(HTS221_H_0_RH);
	h_0_rh=h_0_rh/2;
	uint16_t h_1_rh=(uint16_t)hts221_read_byte(HTS221_H_1_RH);
	h_1_rh=h_1_rh/2;

	hts221_readArray(buffer, HTS221_H_OUT, 2);
	int16_t H_out= (((int16_t)buffer[1])<<8) | (int16_t)buffer[0];
	hts221_readArray(buffer, HTS221_H_0, 2);
	int16_t H0_out= (((int16_t)buffer[1])<<8) | (int16_t)buffer[0];
	hts221_readArray(buffer, HTS221_H_1, 2);
	int16_t H1_out= (((int16_t)buffer[1])<<8) | (int16_t)buffer[0];

	uint8_t humidity=(uint8_t)(((H1_out - H_out)*h_0_rh + (H_out - H0_out)*h_1_rh) / (H1_out -H0_out));
	return humidity;
}

float hts221_get_temp() {
	int16_t msb=hts221_read_byte(HTS221_T1_T0_MSB);

	int16_t msb_T0=(msb & 0x3) << 8;
	int16_t msb_T1=(msb & 0xC) << 6;
	uint8_t buffer_2[2], buffer_4[4];


	hts221_readArray(buffer_2, HTS221_T0_degC_x8, 2);
	int16_t T0_degC= (msb_T0 | (int16_t)buffer_2[0])/8;
	int16_t T1_degC= (msb_T1 | (int16_t)buffer_2[1])/8;

	hts221_readArray(buffer_2, HTS221_T_OUT, 2);
	int16_t T_out= (((uint16_t)buffer_2[1])<<8) | (uint16_t)buffer_2[0];
	hts221_readArray(buffer_4, HTS221_T0_OUT, 4);
	int16_t T0_out= (((uint16_t)buffer_4[1])<<8) | (uint16_t)buffer_4[0];
	int16_t T1_out= (((uint16_t)buffer_4[3])<<8) | (uint16_t)buffer_4[2];

	float temp;
	temp=(float)((T1_out - T_out)*T0_degC + (T_out - T0_out)*T1_degC) / (T1_out -T0_out);
	if (temp >= 120){
		temp = 119.9;
	}
	else if (temp <= -40){
		temp = -39.9;
	}

	return temp;
}


uint8_t hts221_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_DEVICE_ADDRESS);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		val = hts221_read_byte(HTS221_WHO_AM_I_ADDRESS);
		if(val == HTS221_WHO_AM_I_VALUE)
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


	hts221_write_byte(HTS221_CTRL_REG1, HTS221_CTRL_REG1_VAL); 	// zapnutie  senzora a nastavenia

	return status;
}
