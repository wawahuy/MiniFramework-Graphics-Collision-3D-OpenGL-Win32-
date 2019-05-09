/*
	- Mutex.h
	- Project	:	System Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	02/12/2018
	- Update	:
*/

#pragma once
#include <mutex>
#include "Export.h"

namespace yuh {

	class SYSTEM_API Mutex
	{
	public:
		Mutex();
		~Mutex();

		void clock();
		void unclock();

	private:
		std::mutex m_mutex;
	};

} //end yuh