/*
 * SerialMonitor.cpp
 *
 *  Created on: Aug 3, 2021
 *      Author: Arkadiusz Kruszynski
 */

#include "SerialMonitor.h"
#include "ESP8266.h"

extern SerialMonitor Serial;
extern SerialMonitor ESPSerial;


SerialMonitor::SerialMonitor(UART_HandleTypeDef &port, uint8_t size) {
	this->port = &port;
	this->size = size;

}

SerialMonitor::SerialMonitor() {

}

SerialMonitor::~SerialMonitor() {

}

std::string SerialMonitor::ReturnData() {
	std::string temp = this->serialData;
	this->serialData = "";
	return temp;

}

bool SerialMonitor::SendData(std::string message) {
	int n = message.length();
	char tempMessage[n + 1];
	strcpy(tempMessage, message.c_str());

	HAL_StatusTypeDef statusMessage = HAL_UART_Transmit(port,
			(uint8_t*) tempMessage, sizeof tempMessage, 100);
	if (statusMessage != HAL_OK) {
		return false;
	}
	return true;
}

void SerialMonitor::Begin() {
	__HAL_UART_ENABLE_IT(this->port, UART_IT_RXNE);
	if (this->size == 1){
		HAL_UART_Receive_IT(this->port, &this->serialVariable, this->size);
	}
	else{
		HAL_UART_Receive_IT(this->port, this->arrayBufor, this->size);
	}

}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	if (huart->Instance == huart2.Instance) {
		switch (Serial.serialVariable) {

		case ';': {
			Serial.serialData = Serial.charBufor;
			memset(Serial.charBufor, 0, sizeof Serial.charBufor);
			Serial.valuesFromSerial = 0;
			break;
		}
		default: {
			Serial.charBufor[Serial.valuesFromSerial++] =
					Serial.serialVariable;
		}
		}
		HAL_UART_Receive_IT(Serial.port, &Serial.serialVariable, Serial.size);

//	Serial.serialData = (char *)Serial.arrayBufor;
//	HAL_UART_Receive_IT(Serial.port, Serial.arrayBufor, Serial.size);


	}
	if (huart->Instance == huart1.Instance){
		ESPSerial.serialData = (char *)ESPSerial.arrayBufor;
		HAL_UART_Receive_IT(ESPSerial.port, ESPSerial.arrayBufor, ESPSerial.size);

	}




//	if (huart->Instance == huart1.Instance) {
//		switch (*espBoard.espSerial.serialVariable) {
//		case std::to_string(espBoard.connectingESP): {
//			break;
//		}
//		default:{
//
//		}
//		}

}



