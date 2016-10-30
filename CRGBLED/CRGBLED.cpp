#include "CRGBLED.h"

void CRGBLED::setStatus(ENUM_RGB_STATUS status) {
	m_status = status;
}

void CRGBLED::turnOff() {
	m_redLED.turnOff();
	m_greenLED.turnOff();
	m_blueLED.turnOff();
	setStatus(RGB_OFF);
}

CRGBLED::CRGBLED(int portRED, int portGREEN, int portBLUE) {
	m_redLED.setPort(portRED);
	m_greenLED.setPort(portGREEN);
	m_blueLED.setPort(portBLUE);
	setStatus(RGB_OFF);
}

CRGBLED::~CRGBLED() {
}

void CRGBLED::printRGB() {
	cout << "RGB-LED is " << getStatus() << endl;
	cout << "RED port: " << m_redLED.getPort() << endl;
	cout << "GREEN port: " << m_greenLED.getPort() << endl;
	cout << "BLUE port: " << m_blueLED.getPort() << endl;
}

void CRGBLED::turn(ENUM_RGB_STATUS status) {
	turnOff();

	switch (status) {
		case RGB_OFF:
			break;
		case RED:
			m_redLED.turnOn();
			cout << "turn(RED)" << endl;
			setStatus(status);
			break;
		case GREEN:
			m_greenLED.turnOn();
			cout << "turn(GREEN)" << endl;
			setStatus(status);
			break;
		case BLUE:
			m_blueLED.turnOn();
			cout << "turn(BLUE)" << endl;
			setStatus(status);
			break;
		default:
			cout << "ERROR - RGB-LED turn(status)" << endl;
			break;
	}
}

string CRGBLED::getStatus() {
	switch (m_status) {
		case RGB_OFF:
			return "RGB OFF";
		case RED:
			return "red";
		case GREEN:
			return "green";
		case BLUE:
			return "blue";
		default:
			return "ERROR - RGB STATUS";
	}
}
