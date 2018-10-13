#include <iostream>
#include <string>
#include <vector>
#include "Socket.h"
#include "FileManager.h"

int main()
{
	std::string fileName;
	std::cout << "enterFileName for send to server" << std::endl;
	std::cin >> fileName;
	///add check on the correctness of the input file name.
	
	FileManager fileManager;
	fileManager.readFile(fileName);
	Socket socket;
	socket.writeData(fileManager.getBuffer(), fileManager.getFileSize());
	std::vector<char> data;
	while (true)
	{
		char buffer[512];

		int bytesRead = socket.readData(buffer, sizeof(buffer));

		if (bytesRead)
			data.insert(data.end(), buffer, buffer + bytesRead);
		else
			break;
		
	}
	socket.disconnect();
    
}

