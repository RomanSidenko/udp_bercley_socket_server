#include "WinSocket.h"
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_PORT 12345
int ch =0;
WinSocket::WinSocket()
{
	sockaddr_in m_address;
	m_address.sin_family = AF_INET;
	m_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	m_address.sin_port = htons(DEFAULT_PORT);

	if (!openSocket(m_address))
		std::cout << "socket not open" << std::endl;
	else
		std::cout << "Descriptor " << getSocketDescriptor() << std::endl;
	listen(m_descriptor, 5);
}


WinSocket::~WinSocket()
{
	disconnect();
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
	return true;
}

unsigned long WinSocket::readData(char* buf, size_t bufferSize)
{
	int receivedBytes = -1;
	sockaddr_in from;
	int fromLength = static_cast<int>(sizeof(from));

	while (true)
	{
		if (ch == 258)
			std::cout << ch << std::endl;
		receivedBytes = recvfrom(m_descriptor, buf, static_cast<int>(bufferSize), 0, (sockaddr*)&from, &fromLength);

		if (receivedBytes <= 0)
			break;
		else
		{
			ch++;
		
			std::cout << ch << std::endl;
			std::cout << "size" << bufferSize << std::endl;
			break;
		}
			
	}
	//unsigned int fromAddress = ntohl(from.sin_addr.s_addr);
	//unsigned int fromPort = ntohs(from.sin_port);
	return receivedBytes;
}

bool WinSocket::writeData(char* data, size_t bufferSize)
{
	int sent_bytes = sendto(m_descriptor, (const char*)data, static_cast<int>(bufferSize), 0, (sockaddr*)& m_address, sizeof(sockaddr_in));
	if (sent_bytes != bufferSize)
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

bool WinSocket::openSocket(sockaddr_in& address)
{
	init();
	m_descriptor = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if ((m_descriptor == INVALID_SOCKET) || (!bindingSocket(address)) || (!setNonBlockingMode()))
	{
		return false;
		///add error handing open socket
	}
	return true;

}
