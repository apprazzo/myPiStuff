CC = g++
LIBS = -lwiringPi -lwiringPiDev -lpthread
FLAGS = -c

LED_DIR = ../CLED/


exe: CLCD.o $(LED_DIR)CLED.o
	$(CC) -o $@ classtest.cpp CLCD.o $(LED_DIR)CLED.o $(LIBS)

CLCD.o: CLCD.cpp CLCD.h
	$(CC) $(FLAGS) $*.cpp $(LIBS)

CLED.o: $(LED_DIR) CLED.cpp CLED.h
	cd $(LED_DIR) && make CLED.o

clean:
	- rm *.o
	- rm exe
	- rm $(LED_DIR)*.o
	- rm $(LED_DIR)exe
