#ifndef __SBUS_H__
#define __SBUS_H__

#include "stm32f1xx_hal.h"

uint8_t buffer[25];
uint16_t channels[16];

/*!
 * \brief Получает данные по протоколу согласно протоколу sbus
 * \param UART_HandleTypeDef* адресс шины
 */
inline void receive_SBUS(UART_HandleTypeDef* huart);

/*!
 * \brief Возвращает значение ШИМ сигналов в посылке sbus
 * \note количество каналов равно 16
 * \return массив ШИМ сигналов для каналов управления
 */
inline uint16_t* convert_SBUS(void);

#endif /* __SBUS_H__ */
