exe: CLED.o
	g++ -o $@ start.cpp CLED.o -lwiringPi

CLED.o: CLED.cpp CLED.h ENUM_LED_STATUS.cpp
	g++ -c $*.cpp ENUM_LED_STATUS.cpp -lwiringPi
clean:
	- rm *.o
	- rm exe
