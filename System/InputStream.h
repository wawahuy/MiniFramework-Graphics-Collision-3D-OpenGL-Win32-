#pragma once
#include "Export.h"

typedef char byte;

namespace yuh {

	class InputStream
	{
	public:
		virtual	int	 available() = 0;
		virtual	void close() = 0;
		virtual	int  read(byte  &buffer) = 0;
		virtual int  read(byte  *buffer, int len) = 0;
		virtual void seek(int pos) = 0;
		virtual int  tell() = 0;
	};

}