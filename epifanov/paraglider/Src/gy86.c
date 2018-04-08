#include "gy86.h"

HAL_StatusTypeDef check_MS5611(I2C_HandleTypeDef* hi2c1)
{
	return HAL_I2C_IsDeviceReady(hi2c1, ADDRESS_MS5611, 5, 20);
}

HAL_StatusTypeDef read_PROM_MS5611(I2C_HandleTypeDef* hi2c1, uint16_t* coef)
{
	uint8_t prom[2];
	HAL_StatusTypeDef st;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C1_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[0] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C2_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[1] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C3_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[2] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C4_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[3] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C5_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[4] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &PROM_READ_C6_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, prom, 2);
	coef[5] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	return st;
}

HAL_StatusTypeDef set_OSR_MS5611(I2C_HandleTypeDef* hi2c1, uint8_t* OSR)
{
	return HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, OSR, 1);
}

HAL_StatusTypeDef read_ADC_MS5611(I2C_HandleTypeDef* hi2c1, uint32_t* data)
{
	HAL_StatusTypeDef st;

	uint8_t raw[3];

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MS5611, &ADCREAD_MS5611, 1);
	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MS5611, raw,3);

	data[0] = raw[2] << 16 | raw[1] << 8 | raw[0];

	return st;
}

HAL_StatusTypeDef wake_MPU6050(I2C_HandleTypeDef* hi2c1)
{
	HAL_StatusTypeDef st;

	uint8_t d[2];

	d[0] = PWR_MGMT_1_MPU6050;
	d[1] = 0x00;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, (uint8_t *)d, 2);

	return st;
}

HAL_StatusTypeDef set_gyroscope_rate_sampling_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t rate)
{
	HAL_StatusTypeDef st;

	uint8_t d[2];
	d[0] = SMPLRT_DIV_MPU6050;
	d[1] = rate;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050,(uint8_t *)d,2);

	return st;
}

HAL_StatusTypeDef set_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity)
{
	HAL_StatusTypeDef st;

	uint8_t temp;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &GYRO_CONFIG_MPU6050, 1);

	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, &temp, 1);

	temp = (temp & 0xE7) | sensity << 3;
	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &temp, 1);

	return st;
}

HAL_StatusTypeDef set_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity)
{
	HAL_StatusTypeDef st;

	uint8_t temp;

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &ACCEL_CONFIG_MPU6050, 1);

	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, &temp, 1);

	temp = (temp & 0xE7) | sensity << 3;
	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &temp, 1);

	return st;
}

HAL_StatusTypeDef read_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* acc)
{
	HAL_StatusTypeDef st;

	uint8_t data[6];

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &ACCEL_XOUT_H_MPU6050, 1);

	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, data, 6);

	acc[0] = (int16_t)(data[0] << 8 | data[1]);
	acc[1] = (int16_t)(data[2] << 8 | data[3]);
	acc[2] = (int16_t)(data[4] << 8 | data[5]);

	return st;
}

HAL_StatusTypeDef read_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* gyro)
{
	HAL_StatusTypeDef st;

	uint8_t data[6];

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &GYRO_XOUT_H_MPU6050, 1);

	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, data, 6);

	gyro[0] = (int16_t)(data[0] << 8 | data[1]);
	gyro[1] = (int16_t)(data[2] << 8 | data[3]);
	gyro[2] = (int16_t)(data[4] << 8 | data[5]);

	return st;
}

HAL_StatusTypeDef read_temperature_MPU6050(I2C_HandleTypeDef* hi2c1, float* temp)
{
	HAL_StatusTypeDef st;

	uint8_t data[2];

	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &TEMP_OUT_H_MPU6050, 1);

	st =  HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, data, 2);

	temp[0] = (float)((int16_t)(data[0] << 8 | data[1]) / (float)340.0 + (float)36.53);

	return st;
}


HAL_StatusTypeDef enable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1)
{
	HAL_StatusTypeDef st;
//
//	uint8_t temp;
//	uint8_t reg[2] = {INT_ENABLE_MPU6050,0x21};
//	st = HAL_I2C_Master_Transmit_DMA(&hi2c1, ADDRESS_MPU6050, reg, 2);
//
//	uint8_t mpu_reg= INT_PIN_CFG_MPU6050;
//	st = HAL_I2C_Master_Transmit_DMA(&hi2c1, ADDRESS_MPU6050, &mpu_reg, 1);
//
//	st = HAL_I2C_Master_Receive_DMA(&hi2c1, ADDRESS_MPU6050, &temp, 14);
//	temp |= 0x10;
//	reg[0] = INT_PIN_CFG_MPU6050;
//	reg[1] = temp;
//	st = HAL_I2C_Master_Transmit_DMA(&hi2c1, ADDRESS_MPU6050, reg, 2);

	return st;
}
HAL_StatusTypeDef disable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1)
{
    uint8_t reg[2] = {INT_ENABLE_MPU6050,0x00};

	return HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, reg, 2);
}

HAL_StatusTypeDef read_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t* read)
{
	HAL_StatusTypeDef st;

//	uint8_t read;
//
//	uint8_t reg = INT_STATUS_MPU6050;
//
//	st = HAL_I2C_Master_Transmit_DMA(hi2c1, ADDRESS_MPU6050, &reg, 1);
//
//	st = HAL_I2C_Master_Receive_DMA(hi2c1, ADDRESS_MPU6050, &read, 14);

	return st;
}


