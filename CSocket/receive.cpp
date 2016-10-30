#include "CSocket.h"

#include <string>
#include <iostream>

using namespace std;

#define BUF 512

int main() {
	unsigned short PORT = 1111;
	char puff[BUF];
	UDPSocket socket(PORT);
	string clientAddress;
	socket.RecvDataGram(puff, BUF, clientAddress, PORT);
	cout << "Received data: \"" << puff << "\"" << endl;
}
