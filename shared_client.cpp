#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include "shared_client.h"

static void error()
{
	std::cout<<"An error has occured."<<std::endl;
	exit(1);
}

BOOL APIENTRY DllMain(HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    return TRUE;
}

void connectToServer(int port, std::string ipAddr, std::string msg)
{
    int sock_descriptor, buffer;
    buffer = 256;

    const char* ip_addr = ipAddr.c_str();
    const char* message = msg.c_str();
    char server_reply[buffer];

    std::cout<<"Connecting to ["<<ipAddr<<":"<<port<<"]"<<std::endl;

    sock_descriptor = socket(AF_INET, SOCK_STREAM, 0); // AF_INET = IPv4, SOCK_STREAM = TCP

    if (sock_descriptor == -1) error();

    struct sockaddr_in server;

    server.sin_addr.s_addr = inet_addr(ip_addr);
    server.sin_family = AF_INET; // IPv4
    server.sin_port = htons(port);

    if (connect(sock_descriptor, (struct sockaddr *)&server, sizeof(server)) < 0) error();
    else
    {
        std::cout<<"Connected to ["<<ipAddr<<":"<<port<<"]"<<std::endl;

        if (send(sock_descriptor, message, strlen(message), 0) < 0) error();

        std::cout<<"[CLIENT]: "<<message<<std::endl;

        if (recv(sock_descriptor, server_reply, buffer, 0) < 0) error();

        std::cout<<"[SERVER]: " << server_reply<<std::endl;

        std::cout<<"Closing connection..."<<std::endl;
        close(sock_descriptor);
        std::cout<<"Disconnected"<<std::endl;
        
        exit(1);
    }
}