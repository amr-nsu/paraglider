#include <string.h>
#include "processes.h"
#include "sbus.h"

void SensorTask(void * args)
{
	congifurate_HMC5883L(&hi2c1);
	congifurate_MPU6050(&hi2c1);
	congifurate_MS5611(&hi2c1);

	int16_t buffer[3];

	uint8_t pressure_cmd = 0x46;
	uint8_t temreture_cmd = 0x56;
	uint32_t pressure;
	uint32_t temreture;
	int64_t pres;
	int32_t temp;
	int32_t dt;


	uint16_t coef[6];

	read_PROM_MS5611(&hi2c1, coef);

	float acc[3];

	for(;;)
	{ // acc gyro mag
		//data translation for defaul configuration
		read_accelerometer_MPU6050(&hi2c1, buffer);
		((float*)(data+1))[0] = (buffer[0] * .000061f* 9.80665f);
		((float*)(data+1))[1] = (buffer[1] * .000061f* 9.80665f);
		((float*)(data+1))[2] = (buffer[2] * .000061f* 9.80665f);
		read_gyroscope_MPU6050(&hi2c1, buffer);
		((float*)(data+13))[0] = (buffer[0] * .007633f);
		((float*)(data+13))[1] = (buffer[1] * .007633f);
		((float*)(data+13))[2] = (buffer[2] * .007633f);
		read_data_HMC5883L(&hi2c1, buffer);
		((float*)(data+25))[0] = buffer[0];
		((float*)(data+25))[1] = buffer[2];
		((float*)(data+25))[2] = buffer[1];
		set_OSR_MS5611(&hi2c1, D2_2048_MS5611);
		osDelay(7);
		read_ADC_MS5611(&hi2c1, &temreture);
		set_OSR_MS5611(&hi2c1, D1_2048_MS5611);
		osDelay(7);
		read_ADC_MS5611(&hi2c1, &pressure);
		dt = temreture - (coef[4] << 8);
		temp = 2000 + (((dt >> 10) * coef[5]) >> 13);
		pres = (((pressure >> 7)*(coef[0] >> 4)) >> 10) - (coef[1] << 1) + (((dt >> 4) * (( (((coef[2] >> 4)*(pressure >> 7)) >> 11)  - coef[3] ) >> 11)) >> 7);
		((float*)(data+45))[0] = (float)pres;
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		taskYIELD();
	}

}

void TempretureSensorTask(void * args)
{
	wake_MPU6050(&hi2c1);
	float tempreture;
	//uint16_t temp;
	for(;;)
	{
		read_temperature_MPU6050(&hi2c1, &tempreture);
		//temp = (uint16_t)(tempreture * 100);
		//((float*)data)[0] = tempreture;
		taskYIELD();
	}

}

void ComputerTransmitterTask(void * args)
{
	for(;;)
	{
		HAL_UART_Transmit(&huart3, data, 50,100);
		taskYIELD();
	}
}

void RemoteControlReceiverTask(void * args)
{
	for(;;)
	{
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
		HAL_Delay(60);

		receive_SBUS(&huart1);
		channel = convert_SBUS();

		taskYIELD();
	}
}

void PWMManagerTask(void * args)
{
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);

    const uint32_t period = 14800;
    const uint32_t coefHEX = 59200+400;

	for(;;)
	{

		htim2.Instance->CCR1 = coefHEX * channels[1]/period;
		htim2.Instance->CCR2 = coefHEX * channels[2]/period;
		htim2.Instance->CCR3 = coefHEX * channels[3]/period;
		taskYIELD();
	}
}


void ADCManagerTask(void * args)
{

	HAL_ADC_Start_DMA(&hadc1, ADCData, 3);

	for(;;)
	{
		((uint32_t*)(data+37))[0] = ADCData[0];
		((uint32_t*)(data+37))[1] = ADCData[1];
		((uint32_t*)(data+37))[2] = ADCData[2];
		taskYIELD();
	}
}
