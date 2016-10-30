#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <sys/signal.h>
#include <unistd.h>

#include <exception>
#include <stdexcept>

#include <string>
#include <string.h>
#include <strings.h>
#include <iostream>


using namespace std;

class C_TCP_Server {
private:
	int m_port;
	int m_sockfd;
	int m_newsockfd;
	struct sockaddr_in m_serv_addr;
	struct sockaddr_in m_cli_addr;
	socklen_t m_client_length;

public:
	C_TCP_Server();
	C_TCP_Server(int port);
	~C_TCP_Server();

	void create();
	void bind_socket();
	void listen_at_socket();
	void accept_socket();
	void send_msg(const string msg);
	string receive_msg();
	void close_socket();
	
	void set_Port(const int port);
	int get_Port();
};


class TCP_exception : public exception {
private:
	string s;

public:
	TCP_exception(string s);
	virtual ~TCP_exception() throw();
	virtual const char * what() const throw();	
};
