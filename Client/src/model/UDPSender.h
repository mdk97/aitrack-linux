#pragma once

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>

typedef int SOCKET;

/**
	Data sender to Opentrack using UDP
*/
class UDPSender
{
private:
	const int BUFFER_SIZE = sizeof(double) * 6;
	double position_data[6];

	sockaddr_in dest;
	sockaddr_in local;

	SOCKET s;

public:
	std::string ip;
	int port;

	UDPSender(const char* dest_ip, int dest_port);
	~UDPSender();

	/**
		Sends a data vector to opentrack.
		@param data: Size 6 array which contains [X,Y,Z,Yaw,Pitch,Roll].
	*/
	void send_data(double* data);
};