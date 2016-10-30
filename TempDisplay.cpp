#include <wiringPi.h>
#include "CLED/CLED.h"
#include "CLCD/CLCD.h"
#include "CTCPServer/C_TCP_Server.h"
#include "myTime/myTime.h"

#include <string>
#include <iostream>
#include <unistd.h>

#define MAXLEN 128
#define PORT 4321

using namespace std;

int main() {
	wiringPiSetup();
	int dataLines[8] = {4,5,6,7 , 0,0,0,0};
	CLCD myDisplay(4,20 , 4 , 2,3 , dataLines , 8);

	struct hardware {
		CLCD* pDisplay;
	} hw = {&myDisplay};

	myDisplay.writeLine(1, "welcome 2 my Display");

	C_TCP_Server server(12345);
	server.create();
	server.bind_socket();
	server.listen_at_socket();
	for(;;){
		server.accept_socket();
		string txt = server.receive_msg();
		txt = txt.substr(0, txt.find_first_of("\n"));
		server.close_socket();
		cout << "received: " << txt << endl;
		
		myDisplay.writeLine(2, getDateTimeString(DE));
		myDisplay.writeLine(3, "MSG received:");
	
		myDisplay.writeLine(4, txt);
	}

	return 0;
}
