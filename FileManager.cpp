#include "FileManager.h"
#include <iostream>


FileManager::FileManager()
{
}


FileManager::~FileManager()
{
}

unsigned char FileManager::fileName()
{
	return m_fileName;
}

bool FileManager::readFile(const char* fileName)
{
	if ((m_in = fopen("asdasd", "rb")) == NULL)
	{
		std::cout << "File is not open" << std::endl;
		return false;
	}
	m_fileName = *fileName;
	while (!feof(m_in))
	{
		size_t sizeRead = fread(m_buferedFile, 1, sizeof(m_buferedFile), m_in);
		m_fileSize = ftell(m_in);

	}
	return false;
}
