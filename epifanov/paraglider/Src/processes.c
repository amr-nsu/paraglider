#include "processes.h"

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
		HAL_UART_Transmit_DMA(&huart3, data, 18);
		taskYIELD();
	}
}

void RemoteControlReceiverTask(void * args)
{
	uint8_t buffer[25];

	for(;;)
	{
        HAL_UART_Receive_DMA(&huart1, bufferRemoteControl, 25);
		memcpy(buffer, bufferRemoteControl, 25);
		if((buffer[0] == 0x0F) && (buffer[24] == 0x00))
		{
			channels[0] = ((buffer[1] |buffer[2]<<8) & 0x07FF);
			channels[1]  = ((buffer[2]>>3 |buffer[3]<<5)                 & 0x07FF);
			channels[2]  = ((buffer[3]>>6 |buffer[4]<<2 |buffer[5]<<10)  & 0x07FF);
			channels[3]  = ((buffer[5]>>1 |buffer[6]<<7)                 & 0x07FF);
			channels[4]  = ((buffer[6]>>4 |buffer[7]<<4)                 & 0x07FF);
			channels[5]  = ((buffer[7]>>7 |buffer[8]<<1 |buffer[9]<<9)   & 0x07FF);
			channels[6]  = ((buffer[9]>>2 |buffer[10]<<6)                & 0x07FF);
			channels[7]  = ((buffer[10]>>5|buffer[11]<<3)                & 0x07FF);
			channels[8]  = ((buffer[12]   |buffer[13]<<8)                & 0x07FF);
			channels[9]  = ((buffer[13]>>3|buffer[14]<<5)                & 0x07FF);
			channels[10] = ((buffer[14]>>6|buffer[15]<<2|buffer[16]<<10) & 0x07FF);
			channels[11] = ((buffer[16]>>1|buffer[17]<<7)                & 0x07FF);
			channels[12] = ((buffer[17]>>4|buffer[18]<<4)                & 0x07FF);
			channels[13] = ((buffer[18]>>7|buffer[19]<<1|buffer[20]<<9)  & 0x07FF);
			channels[14] = ((buffer[20]>>2|buffer[21]<<6)                & 0x07FF);
			channels[15] = ((buffer[21]>>5|buffer[22]<<3)                & 0x07FF);
		}
		taskYIELD();
	}
}

void PWMManagerTask(void * args)
{
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_3);

    const uint32_t period = 148000;
    const uint32_t coefHEX = 59199+400;


	for(;;)
	{
		htim2.Instance->CCR1 = coefHEX * channels[0]/period;
		htim2.Instance->CCR2 = coefHEX * channels[0]/period;
		htim2.Instance->CCR3 = coefHEX * channels[0]/period;
		taskYIELD();
	}
}
