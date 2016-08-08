#include "CLED.h"
#include <wiringPi.h>

/**
 * Default-Constructor
 * Der Port wird auf -2 gesetzt zur Abgrenzung der Eingabe eines ungültigen Wertes
 */
CLED::CLED() {
	// der port muss ohne setter gesetzt werden, da der setter einen Wert von
	// -2 nicht zulassen würde.
	m_port = -2;
	init();
}

/**
 * Constructor with parameter port
 * @param int port muss im Wertebereich liegen, dieser wird durch den Setter überwacht
 * 		gültiger Wertebereich: 0 <= port <= 7
 * 		liegt der Wert aushalb des Wertebereichs wird er auf -1 gesetzt.
 */
CLED::CLED(int port) {
	m_port = -2;
	setPort(port);
	init();
}

/**
 * set method for m_port
 * @param port int muss überprüft werden, ob es sich um einen gültigen Wert handelt.
 * 		gültiger Wertebereich: 0 <= port <= 7
 *		liegt der Wert aushalb des Wertebereichs wird er auf -1 gesetzt.
 * @return void
 */
void CLED::setPort(int port) {
	if ((port < 0) || (port > 29))
		port = -1;
	m_port = port;
}

/**
 * get method for m_port
 * @return int der Wert von m_port
 */
int CLED::getPort() {
	return m_port;
}

/**
 * set method m_frequency
 * @param double muss positiv sein wird sonst auf 1 gesetzt.
 * @return void
 */
void CLED::setFrequency(double frq) {
	if (frq < 0.1)
		frq = 1;
	m_frequency = frq;
}

/**
 * getter m_frequency
 * @return double gibt die Frequenz zurück mit welcher die LED blinkt,
 * 		wenn diese auf blinken eingestellt ist.
 */
double CLED::getFrequency() {
	return m_frequency;
}

/**
 * turns off the LED and changes STATUS
 * @return void
 */
void CLED::turnOff() {
	digitalWrite(getPort(), LOW);
	setStatus(OFF);
}

/**
 * turns LED ON and changes STATUS
 * @return void
 */
void CLED::turnOn() {
	digitalWrite(getPort(), HIGH);
	setStatus(ON);
}

/**
 * lets LED blink and changes STATUS
 * LED will blink 5 times and turns off afterwards
 * //TODO
 * must be implemented with a thread later on
 * @return void
 */
void CLED::blink() {
	// ausschalten der LED per Funktion setzt den Status der LED
	// kurzzeitig auf OFF bis der Status auf BLINK gesetzt wird.
	turnOff();
	setStatus(BLINK);

	// wiederholtes ein- und auschalten der LED
	// hier wird manuell geschaltet um den Status nicht immer wieder
	// ändern zu müssen.
	for (int i = 0; i < 5; i++) {
		delay(1000/((getFrequency()*2)));
		digitalWrite(getPort(), HIGH);
		delay((1000/(getFrequency()*2)));
		digitalWrite(getPort(), LOW);
	}
}

/**
 * Initialisierung der LED
 * definierten Status herstellen
 * @return void
 */
void CLED::init() {
	// LED-Port als Ausgang definieren
	pinMode(getPort(), OUTPUT);
	setFrequency(1);
	setColor("N/A");
	turnOff();
}

/**
 * setter m_color
 * gibt die Farbe der LED an als string
 * @param string Farbe der LED
 * @return void
 */
void CLED::setColor(string color) {
	m_color = color;
}

/**
 * getter m_color
 * gibt die Farbe der LED an als string
 * @return string Farbe der LED
 */
string CLED::getColor() {
	return m_color;
}

/**
 * Schaltet zwischen den Zuständen ON und OFF um.
 * Ist der Zustand BLINK passiert nichts.
 * @return void
 */
void CLED::toggle() {
	// Zustand überprüfen und umschalten
	switch (checkStatus()) {
	case ON:
		turnOff();
		break;
	case OFF:
		turnOn();
		break;
	}
	//if (checkStatus() == ON)
	//	turnOff();
	//else if (checkStatus() == OFF)
	//	turnOn();
}

/**
 * gibt den Status der LED als string zurück
 * @return string Status der LED
 */
string CLED::getStatus() {
	string status = "undefined";

	// Umwandlung aus dem Enum zum String
	switch (checkStatus()) {
	case DISABLED: 
		status = "disabled";
		break;
	case ON:
		status = "on";
		break;
	case OFF:
		status = "off";
		break;
	case BLINK:
		status = "blink";
		break;
	default:
		status = "unexpected";
	}

	return status;
}

/**
 * wird zum überprüfen des aktuellen Status für die switch-Funktion verwendet.
 * Vergleich ENUM ist einfacher als String, vorallem liegt ENUM schon vor.
 * @return LED_STATUS gibt den ENUM-Wert des Status zurück
 */
LED_Status CLED::checkStatus() {
	return m_status;
}

/**
 * setter m_status
 * Setzt den aktuellen Status der LED.
 * @param LED_Status
 * @return void
 */
void CLED::setStatus(LED_Status status) {
	m_status = status;
}
