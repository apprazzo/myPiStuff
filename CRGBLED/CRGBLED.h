#ifndef CRGBLED_H
#define CRGBLED_H

#include "../CLED/CLED.h"
#include <string>
#include <iostream>
#include <wiringPi.h>

using namespace std;

enum ENUM_RGB_STATUS {RGB_OFF, RED, GREEN, BLUE};

class CRGBLED {
private:
	CLED m_redLED;
	CLED m_greenLED;
	CLED m_blueLED;
	ENUM_RGB_STATUS m_status;
	void setStatus(ENUM_RGB_STATUS status);
	void turnOff();
	
public:
	CRGBLED(int portRED, int portGREEN, int portBLUE);
	~CRGBLED();
	void printRGB();
	void turn(ENUM_RGB_STATUS status);
	string getStatus();
};

#endif
