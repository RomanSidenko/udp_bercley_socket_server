#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <stdio.h>

#define DEFAULT_BUFFER_SIZE 1024

class FileManager
{
public:
	FileManager();
	~FileManager();

	unsigned char fileName();
	bool readFile(const char* fileName);



private:
	char m_fileName;
	unsigned char m_buferedFile[DEFAULT_BUFFER_SIZE];
	unsigned long m_fileSize;
	FILE *m_in;
};

#endif  //FILEMANAGER

