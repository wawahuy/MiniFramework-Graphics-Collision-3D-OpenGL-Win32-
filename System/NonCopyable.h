/*
	- NonCopyable.h
	- Project	:	System Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	03/12/2018
	- Update	:
*/


#pragma once
#include "Export.h"

namespace yuh {

	class SYSTEM_API NonCopyable {
	public:
		NonCopyable();

		~NonCopyable();

	private:
		NonCopyable(const NonCopyable&);

		NonCopyable& operator= (const NonCopyable&);
	};


} //end yuh