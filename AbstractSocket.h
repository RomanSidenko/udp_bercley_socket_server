#ifndef ABSTRACTSOCKET_H
#define ABSTRACTSOCKET_H
#include <string>

#define DEFAULT_BUFFER_SIZE 1024

class sockaddr_in;
class AbstractSocket
{
public:
	AbstractSocket();
	virtual ~AbstractSocket();
	
	virtual bool connectToHost(const std::string& hostName, const unsigned short hostPort) = 0;
	virtual void disconnect() = 0;
	virtual bool bindingSocket(sockaddr_in& address) = 0;
	virtual unsigned long readData(char* buf, unsigned long bufSize) = 0;
	virtual unsigned long writeData(char* data, unsigned long dataSize) = 0;

	

protected:
	int m_descriptor;
	unsigned char m_buffer[DEFAULT_BUFFER_SIZE];
	unsigned long m_bufferSize;
	sockaddr_in* m_address;
	virtual bool openSocket() = 0;

	void setBufferSize(unsigned long bufSize) { m_bufferSize = bufSize; }
	unsigned long getBuferSize() const { return m_bufferSize; }

	int getSocketDescriptor() const { return m_descriptor; }
	

};

#endif // ABSTRACTSOCKET_H

