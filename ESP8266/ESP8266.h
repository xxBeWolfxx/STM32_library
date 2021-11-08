/*
 * ESP8266.h
 *
 *  Created on: 5 paź 2021
 *      Author: Arkadiusz
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include "SerialMonitor.h"
#include "stdio.h"
#include "cstdint"
#include "string"

using namespace std;

class ESP8266 {
private:
	bool flagReady = false;
	bool flagChangedValue = false;
	int receivedValue = 0;

public:
	SerialMonitor *espSerial;


	//Error Codes   E    //
	int errorESP = 10001;

	//Warning Codes    W    //
	int connectingESP = 10000;

	//Approve Codes    A  //
	int readyESP = 10000;

	//Sending codes to ESP ///
	string readyBoard = "A100";
	string launchingRocket = "A200";
	string turnOff = "A300";


	bool ErrorCodes(int code);
	bool WarningCodes(int code);
	bool ApproveCodes(int code);
	bool ReceivedCodes(int code);


	int Connecting();
	bool TurnOff();
	bool ReceiveMessage(string message);
	bool StatusChange();
	int ReturnValue();


	ESP8266(SerialMonitor &serial);
	virtual ~ESP8266();

	void Init();
};

#endif /* ESP8266_H_ */
