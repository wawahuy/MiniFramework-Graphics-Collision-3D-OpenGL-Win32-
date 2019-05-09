#include "FileInputStream.h"


namespace yuh {

	FileInputStream::FileInputStream()
	{
	}

	FileInputStream::FileInputStream(const char* filename)
	{
		m_file = fopen(filename, "r");
	}

	FileInputStream::~FileInputStream()
	{
		close();
	}

	int FileInputStream::available()
	{
		int pos = tell();
		fseek(m_file, 0L, SEEK_END);
		int siz = tell();
		fseek(m_file, pos, SEEK_SET);
		return siz;
	}

	void FileInputStream::close()
	{
		fclose(m_file);
	}

	int FileInputStream::read(byte &buffer)
	{
		return fread(&buffer, sizeof(byte), 1, m_file);
	}

	int FileInputStream::read(byte *buffer, int len)
	{
		int check = fread(buffer, sizeof(byte), len, m_file);
		return check;
	}

	void FileInputStream::seek(int pos)
	{
		fseek(m_file, pos, SEEK_SET);
	}

	int FileInputStream::tell()
	{
		return ftell(m_file);
	}

	std::string FileInputStream::getContent()
	{
		int len = available();
		std::string str;
		str.resize(len);
		int posEof = read(&str[0], len);
		str[posEof] = '\0';
		return str;
	}

}
