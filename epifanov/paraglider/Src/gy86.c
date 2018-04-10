#include "gy86.h"

const uint8_t ADDRESS_MS5611 = 0x77 << 1;
const uint8_t ADCREAD_MS5611 = 0x00;
const uint8_t RESET_MS5611 = 0x1E;
const uint8_t D1_256_MS5611 = 0x40;
const uint8_t D1_512_MS5611 = 0x42;
const uint8_t D1_1024_MS5611 = 0x44;
const uint8_t D1_2048_MS5611 = 0x46;
const uint8_t D1_4096_MS5611 = 0x48;
const uint8_t D2_256_MS5611 = 0x50;
const uint8_t D2_512_MS5611 = 0x52;
const uint8_t D2_1024_MS5611 = 0x54;
const uint8_t D2_2048_MS5611 = 0x56;
const uint8_t D2_4096_MS5611 = 0x58;
const uint8_t PROM_READ_C1_MS5611 = 0xA2;
const uint8_t PROM_READ_C2_MS5611 = 0xA4;
const uint8_t PROM_READ_C3_MS5611 = 0xA6;
const uint8_t PROM_READ_C4_MS5611 = 0xA8;
const uint8_t PROM_READ_C5_MS5611 = 0xAA;
const uint8_t PROM_READ_C6_MS5611 = 0xAC;

const uint8_t ADDRESS_MPU6050 = 0x68 << 1;
const uint8_t SMPLRT_DIV_MPU6050 = 0x19;
const uint8_t CONFIG_MPU6050 = 0x1A;
const uint8_t GYRO_CONFIG_MPU6050 = 0x1B;
const uint8_t ACCEL_CONFIG_MPU6050 = 0x1C;
const uint8_t MOTION_THRESH_MPU6050 = 0x1F;
const uint8_t INT_PIN_CFG_MPU6050 = 0x37;
const uint8_t INT_ENABLE_MPU6050 = 0x38;
const uint8_t INT_STATUS_MPU6050 = 0x3A;
const uint8_t ACCEL_XOUT_H_MPU6050 = 0x3B;
const uint8_t ACCEL_XOUT_L_MPU6050 = 0x3C;
const uint8_t ACCEL_YOUT_H_MPU6050 = 0x3D;
const uint8_t ACCEL_YOUT_L_MPU6050 = 0x3E;
const uint8_t ACCEL_ZOUT_H_MPU6050 = 0x3F;
const uint8_t ACCEL_ZOUT_L_MPU6050 = 0x40;
const uint8_t TEMP_OUT_H_MPU6050 = 0x41;
const uint8_t TEMP_OUT_L_MPU6050 = 0x42;
const uint8_t GYRO_XOUT_H_MPU6050 = 0x43;
const uint8_t GYRO_XOUT_L_MPU6050 = 0x44;
const uint8_t GYRO_YOUT_H_MPU6050 = 0x45;
const uint8_t GYRO_YOUT_L_MPU6050 = 0x46;
const uint8_t GYRO_ZOUT_H_MPU6050 = 0x47;
const uint8_t GYRO_ZOUT_L_MPU6050 = 0x48;
const uint8_t MOT_DETECT_STATUS_MPU6050 = 0x61;
const uint8_t SIGNAL_PATH_RESET_MPU6050 = 0x68;
const uint8_t MOT_DETECT_CTRL_MPU6050 = 0x69;
const uint8_t USER_CTRL_MPU6050 = 0x6A;
const uint8_t PWR_MGMT_1_MPU6050 = 0x6B;
const uint8_t PWR_MGMT_2_MPU6050 = 0x6C;
const uint8_t FIFO_COUNTH_MPU6050 = 0x72;
const uint8_t FIFO_COUNTL_MPU6050 = 0x73;
const uint8_t FIFO_R_W_MPU6050 = 0x74;
const uint8_t WHO_AM_I_MPU6050 = 0x75;

const uint8_t ADDRESS_HMC5883L = 0x1E << 1;
const uint8_t CONF_A_HMC5883L = 0x00;
const uint8_t CONF_B_HMC5883L = 0x01;
const uint8_t MODE_HMC5883L = 0x02;
const uint8_t MAG_XOUT_H_HMC5883L = 0x03;
const uint8_t MAG_XOUT_L_HMC5883L = 0x04;
const uint8_t MAG_YOUT_H_HMC5883L = 0x05;
const uint8_t MAG_YOUT_L_HMC5883L = 0x06;
const uint8_t MAG_ZOUT_H_HMC5883L = 0x07;
const uint8_t MAG_ZOUT_L_HMC5883L = 0x08;
const uint8_t STATUS_HMC5883L = 0x09;
const uint8_t IDENTIFICATION_A = 0x0A;
const uint8_t IDENTIFICATION_B = 0x0B;
const uint8_t IDENTIFICATION_C = 0x0C;

void check_MS5611(I2C_HandleTypeDef* hi2c1)
{
	while (HAL_I2C_IsDeviceReady(hi2c1, ADDRESS_MS5611, 5, 100) != HAL_OK);
}

void read_PROM_MS5611(I2C_HandleTypeDef* hi2c1, uint16_t* coef)
{
	uint8_t prom[2];

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C1_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[0] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C2_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[1] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C3_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[2] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C4_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[3] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C5_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[4] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &PROM_READ_C6_MS5611, 1, 100) != HAL_OK);
	while (HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, prom, 2, 100) != HAL_OK);
	coef[5] = (prom[0] << 8 | prom[1] ) & 0xFFFF;

}

void set_OSR_MS5611(I2C_HandleTypeDef* hi2c1, uint8_t* OSR)
{
	while (HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, OSR, 1, 100)!= HAL_OK);
}

void read_ADC_MS5611(I2C_HandleTypeDef* hi2c1, uint32_t* data)
{
	HAL_StatusTypeDef st;

	uint8_t raw[3];

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MS5611, &ADCREAD_MS5611, 1, 100)!= HAL_OK);
	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MS5611, raw,3, 100)!= HAL_OK);

	data[0] = raw[2] << 16 | raw[1] << 8 | raw[0];

}

void wake_MPU6050(I2C_HandleTypeDef* hi2c1)
{
	uint8_t d[2];

	d[0] = PWR_MGMT_1_MPU6050;
	d[1] = 0x00;

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, (uint8_t *)d, 2, 100) != HAL_OK);
}

void set_gyroscope_rate_sampling_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t rate)
{
	uint8_t d[2];
	d[0] = SMPLRT_DIV_MPU6050;
	d[1] = rate;

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050,(uint8_t *)d,2, 100)!= HAL_OK);
}

void set_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity)
{
	uint8_t temp;

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &GYRO_CONFIG_MPU6050, 1, 100)!= HAL_OK);

	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, &temp, 1, 100)!= HAL_OK);

	temp = (temp & 0xE7) | sensity << 3;
	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &temp, 1, 100)!= HAL_OK);

}

void set_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity)
{
	uint8_t temp;

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &ACCEL_CONFIG_MPU6050, 1, 100)!= HAL_OK);

	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, &temp, 1, 100)!= HAL_OK);

	temp = (temp & 0xE7) | sensity << 3;
	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &temp, 1, 100)!= HAL_OK);

}

void read_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* acc)
{
	HAL_StatusTypeDef st;

	uint8_t data[6];

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &ACCEL_XOUT_H_MPU6050, 1, 100)!= HAL_OK);

	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, data, 6, 100)!= HAL_OK);

	acc[0] = (int16_t)(data[0] << 8 | data[1]);
	acc[1] = (int16_t)(data[2] << 8 | data[3]);
	acc[2] = (int16_t)(data[4] << 8 | data[5]);

}

void read_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* gyro)
{
	HAL_StatusTypeDef st;

	uint8_t data[6];

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &GYRO_XOUT_H_MPU6050, 1, 100)!= HAL_OK);

	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, data, 6, 100)!= HAL_OK);

	gyro[0] = (int16_t)(data[0] << 8 | data[1]);
	gyro[1] = (int16_t)(data[2] << 8 | data[3]);
	gyro[2] = (int16_t)(data[4] << 8 | data[5]);

}

void read_temperature_MPU6050(I2C_HandleTypeDef* hi2c1, float* temp)
{
	HAL_StatusTypeDef st;

	uint8_t data[2];

	while(HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &TEMP_OUT_H_MPU6050, 1, 100)!= HAL_OK);

	while(HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, data, 2, 100)!= HAL_OK);

	temp[0] = (float)((int16_t)(data[0] << 8 | data[1]) / (float)340.0 + (float)36.53);

}


void enable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1)
{

//	uint8_t temp;
//	uint8_t reg[2] = {INT_ENABLE_MPU6050,0x21};
//	st = HAL_I2C_Master_Transmit(&hi2c1, ADDRESS_MPU6050, reg, 2);
//
//	uint8_t mpu_reg= INT_PIN_CFG_MPU6050;
//	st = HAL_I2C_Master_Transmit(&hi2c1, ADDRESS_MPU6050, &mpu_reg, 1);
//
//	st = HAL_I2C_Master_Receive(&hi2c1, ADDRESS_MPU6050, &temp, 14);
//	temp |= 0x10;
//	reg[0] = INT_PIN_CFG_MPU6050;
//	reg[1] = temp;
//	st = HAL_I2C_Master_Transmit(&hi2c1, ADDRESS_MPU6050, reg, 2);

}
void disable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1)
{
//    uint8_t reg[2] = {INT_ENABLE_MPU6050,0x00};
//
//	return HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, reg, 2);
}

void read_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t* read)
{

//	uint8_t read;
//
//	uint8_t reg = INT_STATUS_MPU6050;
//
//	st = HAL_I2C_Master_Transmit(hi2c1, ADDRESS_MPU6050, &reg, 1);
//
//	st = HAL_I2C_Master_Receive(hi2c1, ADDRESS_MPU6050, &read, 14);

}


