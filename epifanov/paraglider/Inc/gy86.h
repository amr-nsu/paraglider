#ifndef __GY86_H__
#define __GY86_H__

#include "stm32f1xx_hal.h"

/*
 *Use case for MS5611:
 *  - read PROM
 *	- set OSR(over sampling rate) mode
 *	- read ADC
 *Use case for MPU6050:
 *  - wake up sensor
 *  - set ranges
 *  - read data from sensor
 *Use case for HMC5883L:
 */

//D2 - temperature, D1 - pressure
const uint8_t ADDRESS_MS5611;
const uint8_t ADCREAD_MS5611;
const uint8_t RESET_MS5611;
const uint8_t D1_256_MS5611;
const uint8_t D1_512_MS5611;
const uint8_t D1_1024_MS5611;
const uint8_t D1_2048_MS5611;
const uint8_t D1_4096_MS5611;
const uint8_t D2_256_MS5611;
const uint8_t D2_512_MS5611;
const uint8_t D2_1024_MS5611;
const uint8_t D2_2048_MS5611;
const uint8_t D2_4096_MS5611;
const uint8_t PROM_READ_C1_MS5611;
const uint8_t PROM_READ_C2_MS5611;
const uint8_t PROM_READ_C3_MS5611;
const uint8_t PROM_READ_C4_MS5611;
const uint8_t PROM_READ_C5_MS5611;
const uint8_t PROM_READ_C6_MS5611;

/*!
 * \brief Проверяет готовность к работе MS5611
 * \param I2C_HandleTypeDef* адресс шины
 * \return статус операции
 */
void check_MS5611(I2C_HandleTypeDef* hi2c1);

/*!
 * \brief Читает PROM память MS5611
 * \note Размер массива должен быть 6 байт
 * \param I2C_HandleTypeDef* адресс шины
 * \param coef массив для возврата коэффицентов
 * \return статус операции
 */
void read_PROM_MS5611(I2C_HandleTypeDef* hi2c1, uint16_t* coef);

/*!
 * \brief Устанавливает OSR MS5611
 * \param I2C_HandleTypeDef* адресс шины
 * \param OSR адресс операции
 * \return статус операции
 */
void set_OSR_MS5611(I2C_HandleTypeDef* hi2c1, uint8_t* OSR);

/*!
 * \brief Читает данные с датчика MS5611
 * \param I2C_HandleTypeDef* адресс шины
 * \param data массив для возврата данных
 * \return статус операции
 */
void read_ADC_MS5611(I2C_HandleTypeDef* hi2c1, uint32_t* data);

const uint8_t ADDRESS_MPU6050;
const uint8_t SMPLRT_DIV_MPU6050;
const uint8_t CONFIG_MPU6050;
const uint8_t GYRO_CONFIG_MPU6050;
const uint8_t ACCEL_CONFIG_MPU6050;
const uint8_t MOTION_THRESH_MPU6050;
const uint8_t INT_PIN_CFG_MPU6050;
const uint8_t INT_ENABLE_MPU6050;
const uint8_t INT_STATUS_MPU6050;
const uint8_t ACCEL_XOUT_H_MPU6050;
const uint8_t ACCEL_XOUT_L_MPU6050;
const uint8_t ACCEL_YOUT_H_MPU6050;
const uint8_t ACCEL_YOUT_L_MPU6050;
const uint8_t ACCEL_ZOUT_H_MPU6050;
const uint8_t ACCEL_ZOUT_L_MPU6050;
const uint8_t TEMP_OUT_H_MPU6050;
const uint8_t TEMP_OUT_L_MPU6050;
const uint8_t GYRO_XOUT_H_MPU6050;
const uint8_t GYRO_XOUT_L_MPU6050;
const uint8_t GYRO_YOUT_H_MPU6050;
const uint8_t GYRO_YOUT_L_MPU6050;
const uint8_t GYRO_ZOUT_H_MPU6050;
const uint8_t GYRO_ZOUT_L_MPU6050;
const uint8_t MOT_DETECT_STATUS_MPU6050;
const uint8_t SIGNAL_PATH_RESET_MPU6050;
const uint8_t MOT_DETECT_CTRL_MPU6050;
const uint8_t USER_CTRL_MPU6050;
const uint8_t PWR_MGMT_1_MPU6050;
const uint8_t PWR_MGMT_2_MPU6050;
const uint8_t FIFO_COUNTH_MPU6050;
const uint8_t FIFO_COUNTL_MPU6050;
const uint8_t FIFO_R_W_MPU6050;
const uint8_t WHO_AM_I_MPU6050;

/*!
 * \brief Меняет режим питания MPU6050
 * \note See register 0x6B
 * \param I2C_HandleTypeDef* адресс шины
 * \return статус операции
 */
void wake_MPU6050(I2C_HandleTypeDef* hi2c1);

/*!
 * \brief Устанавливает значение сэмплирования гироскопа MPU6050
 * \note See register 0x19
 *       Sample rate set to 8 kHz 0
 *       Sample rate set to 4 kHz 1
 *       Sample rate set to 2 kHz 3
 *       Sample rate set to 1 kHz 7
 *       Sample rate set to 500 Hz 15
 *       Sample rate set to 250 Hz 31
 *       Sample rate set to 125 Hz 63
 *       Sample rate set to 100 Hz 79
 * \param I2C_HandleTypeDef* адресс шины
 * \param uint8_t значение сэмплирования
 * \return статус операции
 */
void set_gyroscope_rate_sampling_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t rate);

/*!
 * \brief Устанавливает значение диапазона гироскоп MPU6050
 * \note See register 0x1B
 *       Range is +- 250 degrees/s 0x00
 *       Range is +- 500 degrees/s 0x01
 *       Range is +- 1000 degrees/s 0x02
 *       Range is +- 2000 degrees/s 0x03
 * \param I2C_HandleTypeDef* адресс шины
 * \param sensity значение чувствительности
 * \return статус операции
 */
void set_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity);

/*!
 * \brief Устанавливает значение диапазона акселерометра MPU6050
 * \note See register 0x1C
 *       Range is +- 2G 0x00
 *       Range is +- 4G 0x01
 *       Range is +- 8G 0x02
 *       Range is +- 16G 0x03
 * \param I2C_HandleTypeDef* адресс шины
 * \param sensity значение чувствительности
 * \return статус операции
 */
void set_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t sensity);

/*!
 * \brief Возвращает значение акселерометра MPU6050
 * \param I2C_HandleTypeDef* адресс шины
 * \note Размер массива должен быть 6 байт
 * \param gyro массив для возврата данных с акселерометра
 * \return статус операции
 */
void read_accelerometer_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* acc);

/*!
 * \brief Возвращает значение гироскопа MPU6050
 * \note Размер массива должен быть 6 байт
 * \param I2C_HandleTypeDef* адресс шины
 * \param gyro массив для возврата данных с гироскопа
 * \return статус операции
 */
void read_gyroscope_MPU6050(I2C_HandleTypeDef* hi2c1, int16_t* gyro);

/*!
 * \brief Возвращает значение температуры MPU6050
 * \param I2C_HandleTypeDef* адресс шины
 * \note Размер массива должен быть 4 байт
 * \param float массив для возврата температуры
 * \return статус операции
 */
void read_temperature_MPU6050(I2C_HandleTypeDef* hi2c1, float* data);


//not properly written function
/*!
 * \brief Разрешение прерываний MPU6050
 * \param I2C_HandleTypeDef* адресс шины
 * \return статус операции
 */
void enable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1);

/*!
 * \brief Блокировка прерываний MPU6050
 * \param I2C_HandleTypeDef* адресс шины
 * \return статус операции
 */
void disable_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1);

/*!
 * \brief Чтение прерываний MPU6050
 * \param I2C_HandleTypeDef* адресс шины
 * \param read массив для возврата прерывания
 * \return статус операции
 */
void read_interrupts_MPU6050(I2C_HandleTypeDef* hi2c1, uint8_t* read);
//undefined behaviour

const uint8_t ADDRESS_HMC5883L;
const uint8_t CONF_A_HMC5883L;
const uint8_t CONF_B_HMC5883L;
const uint8_t MODE_HMC5883L;
const uint8_t MAG_XOUT_H_HMC5883L;
const uint8_t MAG_XOUT_L_HMC5883L;
const uint8_t MAG_YOUT_H_HMC5883L;
const uint8_t MAG_YOUT_L_HMC5883L;
const uint8_t MAG_ZOUT_H_HMC5883L;
const uint8_t MAG_ZOUT_L_HMC5883L;
const uint8_t STATUS_HMC5883L;
const uint8_t IDENTIFICATION_A;
const uint8_t IDENTIFICATION_B;
const uint8_t IDENTIFICATION_C;

//0 0 0 0.75
//0 0 1 1.5
//0 1 0 3
//0 1 1 7.5
//1 0 0 15 (Default)
//1 0 1 30
//1 1 0 75
void set_data_output_rate_HMC5883L(I2C_HandleTypeDef* hi2c1, uint8_t rate);

void set_data_output_range_HMC5883L(I2C_HandleTypeDef* hi2c1, uint8_t rate);

void set_operating_mode_HMC5883L(I2C_HandleTypeDef* hi2c1, uint8_t rate);

void read_data_HMC5883L(I2C_HandleTypeDef* hi2c1, uint8_t* data);

void read_status_HMC5883L(I2C_HandleTypeDef* hi2c1, uint8_t* status);

#endif /* __GY86_H__ */
