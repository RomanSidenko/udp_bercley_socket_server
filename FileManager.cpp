#include "FileManager.h"
#include <iostream>


FileManager::FileManager()
	: m_fileName()
	, m_fileSize(0)
	, m_bufferSize(0)
	, m_pos(0)
{
	
}

FileManager::~FileManager()
{
	closeStream();
	
}

std::string FileManager::getFileName() const
{
	return m_fileName;
}

void FileManager::setFileName(std::string& fileName)
{
	m_fileName = fileName;
}

void FileManager::setBufferSize(size_t size)
{
	m_bufferSize = size;
}

bool FileManager::readFile(std::string& fileName)
{
	try
	{
		m_in.open(fileName, std::ios::binary);
		if (!m_in.is_open())
			std::cout << "File is not open" << std::endl;
		else
		{
			m_fileSize = m_in.seekg(0, std::ios::end).tellg();
			m_in.seekg(0, std::ios::beg);
			setFileName(fileName);
		}
	}
	catch (const std::exception& error)
	{
		std::cerr << error.what() << std::endl;
		return (EXIT_FAILURE);
	}

	return true;
}

bool FileManager::writeFile(char* buffer, std::string fileName = std::string())
{
	if (fileName.empty() && !m_fileName.empty())
		fileName = m_fileName;
	if (!m_out.is_open())
	{
		m_out.open(fileName, std::ios::binary);
		if (!m_out.is_open())
			std::cout << "File is not open" << std::endl;
		else
		{
			m_out.write(buffer, sizeof(buffer));
			m_pos += sizeof(buffer);
		}
	}
	else
	{
		m_out.write(buffer, sizeof(buffer));
		m_pos += sizeof(buffer);
	}
		
	/*if (sizeof(buffer) != 1024)
	{
		m_out.close();
		return false;
	}*/
	return true;
}

std::streamsize FileManager::getFileSize()
{
	return m_fileSize;
}



size_t FileManager::getBufferSize() const
{
	return m_bufferSize;
}

std::streampos FileManager::getPos()
{
	return m_pos;
}

void FileManager::closeStream()
{
	m_in.close();
}

char * FileManager::getBuffer()
{
	char buffer[1024];
	memset(&buffer, 0, sizeof(buffer));
	m_in.read(buffer, sizeof(buffer));
	if (m_in.eof())
		setBufferSize(std::abs(m_pos - m_fileSize));
	else
	{
		m_pos = m_in.tellg();
		m_in.seekg(m_pos);
		setBufferSize(sizeof(buffer));
	}
	return buffer;
}

