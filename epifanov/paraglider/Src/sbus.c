#include "sbus.h"

inline void receive_SBUS(UART_HandleTypeDef* huart)
{
	uint8_t bufferRemoteControl[25];
	HAL_UART_Receive_DMA(huart, bufferRemoteControl, 25);
	memcpy(buffer, bufferRemoteControl, 25);
}

inline uint16_t* convert_SBUS(void)
{
	if((buffer[0] == 0x0F) && (buffer[24] == 0x00))
	{
		channels[0]  = ((buffer[1]  >> 0 | buffer[2]  << 8                    ) & 0x07FF);
		channels[1]  = ((buffer[2]  >> 3 | buffer[3]  << 5                    ) & 0x07FF);
		channels[2]  = ((buffer[3]  >> 6 | buffer[4]  << 2 | buffer[5]  << 10 ) & 0x07FF);
		channels[3]  = ((buffer[5]  >> 1 | buffer[6]  << 7                    ) & 0x07FF);
		channels[4]  = ((buffer[6]  >> 4 | buffer[7]  << 4                    ) & 0x07FF);
		channels[5]  = ((buffer[7]  >> 7 | buffer[8]  << 1 | buffer[9]  << 9  ) & 0x07FF);
		channels[6]  = ((buffer[9]  >> 2 | buffer[10] << 6                    ) & 0x07FF);
		channels[7]  = ((buffer[10] >> 5 | buffer[11] << 3                    ) & 0x07FF);
		channels[8]  = ((buffer[12] >> 0 | buffer[13] << 8                    ) & 0x07FF);
		channels[9]  = ((buffer[13] >> 3 | buffer[14] << 5                    ) & 0x07FF);
		channels[10] = ((buffer[14] >> 6 | buffer[15] << 2 | buffer[16] << 10 ) & 0x07FF);
		channels[11] = ((buffer[16] >> 1 | buffer[17] << 7                    ) & 0x07FF);
		channels[12] = ((buffer[17] >> 4 | buffer[18] << 4                    ) & 0x07FF);
		channels[13] = ((buffer[18] >> 7 | buffer[19] << 1 | buffer[20] << 9  ) & 0x07FF);
		channels[14] = ((buffer[20] >> 2 | buffer[21] << 6                    ) & 0x07FF);
		channels[15] = ((buffer[21] >> 5 | buffer[22] << 3                    ) & 0x07FF);
	}

	return channels;
}
