#include "FileManager.h"
#include <iostream>


FileManager::FileManager()
{
	allocMemoryForBuff(m_buffer, getFileSize());
}


FileManager::~FileManager()
{
	delete m_buffer;
}

char FileManager::getFileName() const
{
	return m_fileName;
}

void FileManager::setFileName(const char * fileName)
{
	m_fileName = *fileName;
}

bool FileManager::readFile(const char* fileName)
{
	if ((m_in = fopen(fileName, "rb")) == NULL)
	{
		std::cout << "File is not open" << std::endl;
		return false;
	}
	setFileName(fileName);
	return true;
}

bool FileManager::formBuffer()
{
	size_t sizeRead;
	while (!feof(m_in))
	{
		sizeRead = fread(m_buffer, 1, sizeof(m_buffer), m_in);
	}
	if (sizeRead <= 0 || sizeRead != m_fileSize)
	{
		///error
		return false;
	}
	return true;
}

unsigned long FileManager::getFileSize()
{
	fseek(m_in, 0, SEEK_END);							// устанавливаем позицию в конец файла
	m_fileSize = ftell(m_in);                           // получаем размер в байтах
	rewind(m_in);										// устанавливаем указатель в конец файла
	return m_fileSize;
}

char * FileManager::getBuffer() const
{
	return m_buffer;
}

bool FileManager::allocMemoryForBuff(char * buffer, unsigned long fileSize)
{
	m_buffer = (char*)malloc(sizeof(char) * m_fileSize);
	if (m_buffer == NULL)
	{
		std::cout << "Memory malloc for bufer error" << std::endl;
		return false;
	}
	return true;
}
