#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int port, sock_descriptor, buffer;
	std::string ipAddr, msg;

	if (argc < 4)
	{
		std::cout<<"Error: Not arguments delivered"<<std::endl;
		return 0;
	}

	ipAddr = argv[1];
	port = std::stoi(argv[2]);
	msg = argv[3];

	buffer = 256;

	std::cout<<"Connecting to ["<<ipAddr<<":"<<port<<"]"<<std::endl;

	sock_descriptor = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP

	if (sock_descriptor == -1)
	{
		std::cout<<"Error: couldn't create socket connection"<<std::endl;
		return 0;
	}

	struct sockaddr_in server;
	const char *ip_addr = ipAddr.c_str();
	const char *message = msg.c_str();
	char server_reply[buffer];

	server.sin_addr.s_addr = inet_addr(ip_addr);
	server.sin_family = AF_INET; // IPv4
	server.sin_port = htons(port);

	if (connect(sock_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
		std::cout<<"Error: Couldn't connect to server"<<std::endl;
		return 0;
	}
	else
	{
		std::cout<<"Connected to ["<<ipAddr<<":"<<port<<"]"<<std::endl;

		if (send(sock_descriptor, message, strlen(message), 0) < 0)
		{
			std::cout<<"Error: Couldn't send message to server"<<std::endl;
			return 0;
		}
		std::cout<<"[CLIENT]: "<<message<<std::endl;

		if (recv(sock_descriptor, server_reply, buffer, 0) < 0)
		{
			std::cout<<"Error: Couldn't read from server"<<std::endl;
			return 0;
		}

		std::cout<<"[SERVER]: " << server_reply<<std::endl;

		std::cout<<"Closing connection..."<<std::endl;
		close(sock_descriptor);
		std::cout<<"Disconnected"<<std::endl;
		
		exit(1);
	}

	return 1;
}
