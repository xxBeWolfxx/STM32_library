/*
 * SerialMonitor.h
 *
 *  Created on: Aug 3, 2021
 *      Author: Arkadiusz Kruszyński
 */
#include "cstdint"
#include "usart.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_uart.h"
#include "stdio.h"
#include "string.h"
#include "string"


#ifndef SRC_SERIALMONITOR_H_
#define SRC_SERIALMONITOR_H_

class SerialMonitor {
private:



public:
	uint8_t serialVariable;
	char charBufor[100];
	uint8_t arrayBufor[20];

	uint8_t size = 0;

	std::string serialData;
	UART_HandleTypeDef *port;
	uint16_t valuesFromSerial;


	bool SendData(std::string message);
	std::string ReturnData();
	void Begin();






	SerialMonitor();
	SerialMonitor( UART_HandleTypeDef &port, uint8_t size);
	virtual ~SerialMonitor();
};

#endif /* SRC_SERIALMONITOR_H_ */
