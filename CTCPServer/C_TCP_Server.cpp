#include "C_TCP_Server.h"

using namespace std;

C_TCP_Server::C_TCP_Server() {
	set_Port(12345);
}

C_TCP_Server::C_TCP_Server(int port) {
	set_Port(port);
}

C_TCP_Server::~C_TCP_Server() {
	;
}


void C_TCP_Server::create() { //throw (TCP_exception) {
	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockfd < 0) {
		throw TCP_exception("creating socket failed");
	}
}

void C_TCP_Server::bind_socket() {
	bzero((char *) &m_serv_addr, sizeof(m_serv_addr));
	m_serv_addr.sin_family = AF_INET;
	m_serv_addr.sin_addr.s_addr = INADDR_ANY;
	m_serv_addr.sin_port = htons(get_Port());

	if (bind(m_sockfd, (struct sockaddr *) &m_serv_addr, sizeof(m_serv_addr)) < 0) {
		throw TCP_exception("binding socket failed");
	}
}

void C_TCP_Server::listen_at_socket() {
	listen(m_sockfd,1);
}

void C_TCP_Server::accept_socket() {
	m_client_length = sizeof(m_client_length);
	m_newsockfd = accept(m_sockfd, (struct sockaddr *) &m_cli_addr, &m_client_length);
	
	if (m_newsockfd < 0) {
		throw TCP_exception("accepting failed");
	}
}

void C_TCP_Server::send_msg(const string msg) {
	char buffer[msg.length()];
	strcpy(buffer, msg.c_str());
	if (write(m_newsockfd, buffer, msg.length()) < 0) {
		throw TCP_exception("sending a msg failed");
	}
}

string C_TCP_Server::receive_msg() {
	int bufferlength = 255;
	char buffer[bufferlength];
	int msglength;
	msglength = read(m_newsockfd, buffer, bufferlength);
	if (msglength < 0) {
		throw TCP_exception("receving a msg failed");
	}
	else {
		string msg(buffer);
		return msg;
	}
}

void C_TCP_Server::close_socket() {
	if (close(m_newsockfd) < 0) {
		throw TCP_exception("closing socket failed");
	}
}

void C_TCP_Server::set_Port(const int port) {
	if ((port >= 1024) && (49151)) {
		m_port = port;
	}
	else {
		throw invalid_argument("illegal port number");
	}
}

int C_TCP_Server::get_Port() {
	return m_port;
}



TCP_exception::TCP_exception(string s) {
	this->s = s;
}

TCP_exception::~TCP_exception() throw() {}

const char * TCP_exception::what() const throw() {
	return s.c_str();
}
