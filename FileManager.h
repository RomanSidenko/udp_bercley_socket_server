#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <string>
#include <stdio.h>


class FileManager
{
public:
	FileManager();
	~FileManager();

	char getFileName() const;
	void setFileName(const char* fileName);
	bool readFile(const char* fileName);
	bool formBuffer();
	unsigned long getFileSize();
	char* getBuffer() const;




private:
	char m_fileName;
	unsigned long m_fileSize;
	char* m_buffer;
	FILE* m_in;

	bool allocMemoryForBuff(char* buffer, unsigned long fileSize);
	
};

#endif  //FILEMANAGER

