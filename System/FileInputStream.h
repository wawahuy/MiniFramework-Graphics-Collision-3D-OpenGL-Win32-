#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <fstream>
#include <memory>
#include "InputStream.h"
#include "NonCopyable.h"



namespace yuh {

	class SYSTEM_API FileInputStream : public InputStream, NonCopyable
	{
	public:
		FileInputStream();
		FileInputStream(const char* filename);
		virtual ~FileInputStream();

		int	 available();
		void close();
		int  read(byte  &buffer);
		int  read(byte  *buffer, int len);
		void seek(int pos);
		int	 tell();

		std::string getContent();

	private:
		FILE *m_file;
	};

}