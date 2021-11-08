/*
 * ESP8266.cpp
 *
 *  Created on: 5 paź 2021
 *      Author: arkad
 */

#include <ESP8266.h>

ESP8266::ESP8266(SerialMonitor &serial) {
	this->espSerial = &serial;

	// TODO Auto-generated constructor stub

}

ESP8266::~ESP8266() {
	// TODO Auto-generated destructor stub
}

int ESP8266::Connecting() {
	this->espSerial->Begin();
	while (!this->flagReady) {
		this->espSerial->SendData(this->readyBoard);
		string temp = this->espSerial->ReturnData();
		if (temp == "A10000") {
			this->flagReady = true;
		}
		HAL_Delay(500);
	}
	return 1;
}

bool ESP8266::TurnOff() {
	if (flagReady) {
		this->espSerial->SendData(this->turnOff);
		this->flagReady = false;
		return true;
	}
	return false;
}

bool ESP8266::ReceiveMessage(string message) {
	char firstCode = message[0];
	int code = stoi(message.substr(0));
	bool tempFlag = false;

	switch (firstCode) {
	case 'E': {
		tempFlag = this->ErrorCodes(code);
		break;
	}
	case 'W':{
		tempFlag = this->WarningCodes(code);
		break;
	}
	case 'A':{
		tempFlag = this->ApproveCodes(code);
		break;
	}
	case 'T':{
		tempFlag = this->ReceivedCodes(code);
		break;
	}
	}

	return tempFlag;
}

bool ESP8266::ErrorCodes(int code){
	if (code == this->errorESP){
		this->flagReady = false;
	}
	return true;
}

bool ESP8266::WarningCodes(int code){
	if(code == this->connectingESP){

	}

	return true;
}

bool ESP8266::ApproveCodes(int code){
	if(code == this->readyESP){
		this->flagReady = true;
	}

	return true;
}

bool ESP8266::ReceivedCodes(int code){
	this->receivedValue = code;
	this->flagChangedValue = true;

	return true;
}


bool ESP8266::StatusChange(){
	return this->flagChangedValue;
}

int ESP8266::ReturnValue(){
	this->flagChangedValue = false;
	return this->receivedValue;

}
