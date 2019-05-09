#include "Thread.h"
/////////////////////////////////////////////////////////////////////////////////
// Thread.cpp
//
// AUTHOR: Nguyen Gia Huy
// CREATED: 06-08-2018
// UPDATED: 
//
// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
// 
// Copyright (C) Nguyen Gia Huy 2018
/////////////////////////////////////////////////////////////////////////////////


namespace yuh {

	Thread::Thread(std::function<void()> m_call)
	{
		this->m_call = m_call;
		m_flag_cb = true;
	}

	std::shared_ptr<Thread> Thread::create(std::function<void()> m_run)
	{
		return ThreadPtr(new Thread(m_run));
	}

	std::shared_ptr<Thread> Thread::create()
	{
		return ThreadPtr(new Thread());
	}

	Thread::~Thread()
	{
		CloseHandle(m_handle);
	}

	void Thread::Run()
	{
		if (m_flag_cb) m_call();
	}

	void Thread::start()
	{
		m_handle = CreateThread(NULL, 0, StaticRun, this, 0, &m_id);
		WaitForSingleObject(m_handle, 50);	//doi doi chuoi thu 2 duoc thuc hien
	}

	void Thread::setMethodRun(std::function<void()> m_run)
	{
		m_flag_cb = true;
		m_call = m_run;
	}

	unsigned long Thread::StaticRun(LPVOID p)
	{
		if (!p) {
			cout << "loi object!" << endl;
			return -1;
		}

		Thread *t = (Thread*)p;
		t->Run();
		return 1;
	}

} //end yuh