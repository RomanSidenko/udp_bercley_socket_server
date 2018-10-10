#pragma once
#include "AbstractSocket.h"
class UnixSocket :
	public AbstractSocket
{
public:
	UnixSocket();
	~UnixSocket();

	bool connectToHost(const std::string& hostName, const unsigned short hostPort) override;
	virtual void disconnect() override;
	virtual bool bindingSocket(sockaddr_in& address) override;
	virtual unsigned long readData(char* buf, unsigned long bufSize) override;
	virtual unsigned long writeData(char* data, unsigned long dataSize) override;

private:
	bool setNonBlockingMode();
	bool openSocket() override;
};

