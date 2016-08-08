#include "CLCD.h"
#include "../CLED/CLED.h"

#include <wiringPi.h>
#include <lcd.h>

#include <iostream>


using namespace std;

CLCD::CLCD(int lines, int rows, int bitmode, int rs, int enable, int dataLines[], int light) {
	init();

	setLines(lines);
	setRows(rows);
	setBitMode(bitmode);
	setDataLines(dataLines);
	setRS(rs);
	setEnable(enable);
	setLight(light);

	m_lcd = lcdInit(m_lines, m_rows, m_bitMode, m_rs, m_enable, m_dataLines[0], m_dataLines[1], m_dataLines[2], m_dataLines[3], m_dataLines[4], m_dataLines[5], m_dataLines[6], m_dataLines[7]);

	lcdPuts(m_lcd, "Dingsbumsda");

	if (m_lcd < 0) {
		cerr << "initializing LCD failed" << endl;
	}

	clearLCD();
	writeLine(1, "welcome");
}

void CLCD::setLines(int lines) {
	// checking if lines is valid argument ( 0 < lines <= 4)
	if (lines <= 0) {
		cerr << "illegal argument for lines. lines(" << lines << ") <= 0" << endl;
	} else {
		if (lines > 4) {
			cerr << "illegal argument for lines. lines(" << lines << ") > 4" << endl;
		} else {
			m_lines = lines;
		}
	}
}

void CLCD::init() {
	// initializing m_dataLines
	for (int i = 0; i < 8; i++) {
		m_dataLines[i] = -1;
	}
	m_lcd = -1;
	setLines(1);
	setRows(1);
	setBitMode(4);

	m_rs = -1;
	m_enable = -1;
}

void CLCD::setRows(int rows) {
	// checking if rows is valid argument ( 0 < rows <= 20)
	if (rows <= 0) {
		cerr << "illegal argument for rows. rows(" << rows << ") <= 0" << endl;
	} else {
		if (rows > 20) {
			cerr << "illegal argument for rows. rows (" << rows << ") > 20" << endl;
		} else {
			m_rows = rows;
		}
	}
}

void CLCD::setBitMode(int bitMode) {
	// checking if bitmode is 4 or 8
	if ((bitMode == 4) || (bitMode ==8)) {
		m_bitMode = bitMode;
	} else {
		cerr << "illegal argument for bitmode. bitmode (" << bitMode << ") is not 4 or 8" << endl;
	}
}

void CLCD::setDataLines(int dataLines[]) {
	// checking each data in array
	for (int i = 0; i < 8; i++) {
		if ((dataLines[i] >= -1) && (dataLines[i] <= 29)) {
			m_dataLines[i] = dataLines[i];
		} else {
			cerr << "illegal argument for dataLines[" << i << "](" << dataLines[i] << "). Not within the limits (-1 to 29)" << endl;
		}
	}
}

void CLCD::setRS(int rs) {
	// checking if rs is a valid port (0-29)
	if ((rs >= 0) && (rs <= 29)) {
		m_rs = rs;
	} else {
		cerr << "illegal argument for rs(" << rs << "). not a valid port (0 to 29)" << endl;
	}
}

void CLCD::setEnable(int enable) {
	// checking if enable is a valid port (0-29)
	if ((enable >= 0) && (enable <= 29)) {
		m_enable = enable;
	} else {
		cerr << "illegal argument for enable(" << enable << "). not a valid port (0-29)." << endl;
	}
}

void CLCD::setLight(int light) {
	// checking if light is a valid port (0-29)
	if ((light >= 0) && (light <= 29)) {
		m_light.setPort(light);
		turnLightOn();
	} else {
		cerr << "illegal argument for light(" << light << "). not a valid port (0-29)." << endl;
	}
}

void CLCD::turnLightOn() {
	m_light.turnOn();
	setIsLightOn(true);
}

void CLCD::turnLightOff() {
	m_light.turnOff();
	setIsLightOn(false);
}

void CLCD::writeLine(int line, string text) {
	// set cursor position
	line--;
	lcdPosition(m_lcd, 0, line);

	// adjust string length to display/line (rows) length
	if (text.length() <= (unsigned int) m_rows) {
		while (text.length() < (unsigned int) m_rows) {
			text.append(" ");
		}
			lcdPuts(m_lcd, text.c_str());
	} else {
		cerr << "illegal argument for the string. string is too long." << endl;
	}
}

void CLCD::clearLCD() {
	lcdClear(m_lcd);
}

void CLCD::writeChar(int line, int row, char charakter) {
	lcdPosition(m_lcd, row, line);
	lcdPutchar(m_lcd, charakter);
}
