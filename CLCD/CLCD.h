#ifndef CLCD_H
#define CLCD_H

#include <string>
#include <iostream>
#include <wiringPi.h>

#include "../CLED/CLED.h"

using namespace std;

class CLCD {
private:
	// member variables
	int m_lcd;
	int m_lines;
	int m_rows;
	int m_bitMode;
	int m_dataLines[8];
	int m_rs;
	int m_enable;
	CLED m_light;
	bool m_isLightOn;

	// private setter/getter
	void setIsLightOn(bool status) {m_isLightOn = status;};
	void setLines(int lines);
	void setRows(int rows);
	void setBitMode(int bitMode);
	void setRS(int rs);
	void setDataLines(int dataLines[8]);
	void setEnable(int enable);
	void setLight(int light);

	// private method
	void init();

public:
	// Constructor
	CLCD(int lines, int rows, int bitmode, int rs, int enable, int dateLines[], int light);

	// public setter/getter
	int getLines() {return m_lines;};
	int getRows() {return m_rows;};
	int getBitMode() {return m_bitMode;};
//	void getDataLines(int& dataLines[]) {for (int i = 0; i<8; i++) {dataLines[i] = m_dataLines[i];}};
	int getRS() {return m_rs;};
	int getEnable() {return m_enable;};
//	int getLight() {return m_light;};
	bool isLightOn() {return m_isLightOn;};

	// pubic methods
	void turnLightOn();
	void turnLightOff();
	void writeLine(int line, string text);
	void clearLCD();
	void writeChar(int line, int row, char charakter);
};

#endif
