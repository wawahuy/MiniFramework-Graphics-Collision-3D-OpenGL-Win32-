#include "Mutex.h"


namespace yuh {

	Mutex::Mutex()
	{
	}


	Mutex::~Mutex()
	{
	}

	void Mutex::clock()
	{
		m_mutex.lock();
	}

	void Mutex::unclock()
	{
		m_mutex.unlock();
	}

} // end yuh