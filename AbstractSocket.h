#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H
#include <string>

class AbstractSocket
{
public:
	AbstractSocket();
	virtual ~AbstractSocket();
	
	virtual bool connectToHost(const std::string& hostName, const unsigned short hostPort) = 0;
	virtual void disconnect() = 0;
	virtual bool bind() = 0;
	

protected:
	int m_descriptor;
	socketaddr_in m_address;
	int getDescriptor();

};

#endif // ABSTRACTSOCKET_H

