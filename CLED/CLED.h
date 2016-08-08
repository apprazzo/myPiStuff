#ifndef CLED_H
#define CLED_H

#include <string>
#include <iostream>
#include "ENUM_LED_STATUS.cpp"

using namespace std;

class CLED {
private:
	int m_port;
	string m_color;
	LED_Status m_status;
	void init();
	void setStatus(LED_Status status);
	double m_frequency;
	LED_Status checkStatus();
public:
	CLED();
	CLED(int port);
	int getPort();
	void setPort(int port);
	double getFrequency();
	void setFrequency(double frq);
	string getColor();
	void setColor(string color);
	string getStatus();
	void turnOff();
	void turnOn();
	void toggle();
	void blink();
};

#endif
