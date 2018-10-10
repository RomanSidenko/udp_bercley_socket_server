#include "WinSocket.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 12345

WinSocket::WinSocket()
{
	sockaddr_in m_address;
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	m_address.sin_port = htons(DEFAULT_PORT);

	if (!openSocket())
		std::cout << "socket not open" << std::endl;
	else
		std::cout << "Descriptor " << getSocketDescriptor() << std::endl;
	listen(m_descriptor, 5);
}


WinSocket::~WinSocket()
{
}

bool WinSocket::connectToHost(const std::string & hostName, const unsigned short hostPort)
{
	return false;
}

void WinSocket::disconnect()
{
	closesocket(m_descriptor);
	WSACleanup();
}

bool WinSocket::bindingSocket(sockaddr_in& address)
{
	if (bind(m_descriptor, (const sockaddr*)& address, sizeof(sockaddr_in)) < 0)
	{
		return false;
		///add error handling
	}
	return false;
}

unsigned long WinSocket::readData(char* buf, unsigned long bufSize)
{
	int received_bytes = -1;
	while (true)
	{
		unsigned char packet_data[256];
		unsigned int maximum_packet_size = sizeof(packet_data);



		sockaddr_in from;
		int fromLength = sizeof(from);

		received_bytes = recvfrom(m_descriptor, (char*)packet_data, maximum_packet_size, 0, (sockaddr*)&from, &fromLength);

		if (received_bytes <= 0)
			break;
		else
			std::cout << "packet" << packet_data;

		unsigned int from_address = ntohl(from.sin_addr.s_addr);
		unsigned int from_port = ntohs(from.sin_port);
	}
	return received_bytes;
}

unsigned long WinSocket::writeData(char* data, unsigned long dataSize)
{
	int sent_bytes = sendto(m_descriptor, (const char*)data, dataSize, 0, (sockaddr*)& m_address, sizeof(sockaddr_in));
	if (sent_bytes != dataSize)
	{
		return false;
		std::cout << "failed to send packet" << std::endl;
		///add error handling
	}
	return true;
}

int WinSocket::init()
{
	WSADATA wsaData;
	if (FAILED(WSAStartup(MAKEWORD(2, 2), &wsaData)))
	{
		return false;
		///add error handling
	}
	return true;
}

bool WinSocket::setNonBlockingMode()
{
	DWORD nonBlocking = 1;
	if (ioctlsocket(m_descriptor, FIONBIO, &nonBlocking) != 0)
	{
		return false;
		///add error handling
	}
	return true;
}

bool WinSocket::openSocket()
{
	
	init();
	m_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if ((m_descriptor == INVALID_SOCKET) || (!bindingSocket(*m_address)) || (!setNonBlockingMode()))
	{
		return false;
		///add error handing open socket
	}
	if (m_descriptor == INVALID_SOCKET)
	{
		return false;
	}
	if (!bindingSocket(*m_address))
	{
		return false;
	}
	if (!setNonBlockingMode())
	{
		return false;
	}
	return true;

}
