#include "CLED.h"
#include <iostream>
#include <wiringPi.h>


using namespace std;


int main() {
	wiringPiSetup();
	CLED led(0);
	led.setFrequency(3);
	CLED ledRED(1);
	ledRED.turnOn();
	cout << "LED is at port: " << led.getPort()
		<< " and its frequency is: " << led.getFrequency() << endl;
	led.toggle();
	delay(1000);
	led.toggle();
	led.blink();
	ledRED.turnOff();
	//led.blink();
	return 0;
}
