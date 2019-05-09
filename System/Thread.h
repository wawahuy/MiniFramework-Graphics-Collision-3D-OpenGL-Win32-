#pragma once
/////////////////////////////////////////////////////////////////////////////////
// Thread.h
//
// AUTHOR: Nguyen Gia Huy
// CREATED: 06-08-2018
// UPDATED: 
//
// Email: kakahuy99@gmail.com, kakahuy104@gmail.com
// 
// Copyright (C) Nguyen Gia Huy 2018
/////////////////////////////////////////////////////////////////////////////////
#ifndef __THREAD_H
#define __THREAD_H

#include <Windows.h>
#include <exception>
#include <iostream>
#include <functional>
#include <memory>
#include "Mutex.h"
#include "NonCopyable.h"
using namespace std;

namespace yuh {

	/* Multi child process
	 * Create Thread with Thread::create container by ThreadPtr
	 * Support inhear
	 *
	 */
	class SYSTEM_API Thread : public NonCopyable
	{
	public:
		/* Container by ThreadPtr
		 * Call method by ->
		 * Use thread_ptr
		 *
		 */
		static std::shared_ptr<Thread> create(std::function<void()> run);

		/* Container by ThreadPtr
		 * Call method by ->
		 * Use thread_ptr
		 *
		 */
		static std::shared_ptr<Thread> create();

		virtual ~Thread();

		void start();

		void setMethodRun(std::function<void()> run);

	//protected:
		/*
		 - Khởi tạo tiến trình riêng
		 - Không bao gồm các hoạt động đồ họa trên tiến trình
		 - Không dùng cách này để tạo con trỏ thay vào đó hãy sử dụng
				ThreadPtr t = Thread::create(....)
		*/
		Thread() {}

		/*
		 - Khởi tạo tiến trình riêng
		 - Không bao gồm các hoạt động đồ họa trên tiến trình
		 - Không dùng cách này để tạo con trỏ thay vào đó hãy sử dụng
				ThreadPtr t = Thread::create(....)
		*/
		Thread(std::function<void()> m_call);


	private:
		static unsigned long __stdcall StaticRun(LPVOID p);

		virtual void			Run();
		void				   *m_handle;
		std::function<void()>	m_call;
		bool					m_flag_cb = false;
		unsigned long			m_id;
	};


	/* Thread Point Smart
	 * Use with Thread::create()
	 *
	 */
	typedef std::shared_ptr<Thread> ThreadPtr;

}	//end yuh

#endif

