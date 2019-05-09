/*
	- AddressInfo.cpp
	- Address Socket Information!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	27/11/2018
	- Update	:   01/12/2018
*/

#pragma once
#define WIN32_LEAN_AND_MEAN
#include <iostream>
#include <string>
#include <memory>
#include <Windows.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#include "Export.h"

namespace yuh {
	namespace net {

		class NETWORK_API AddressInfo
		{
		public:
			AddressInfo();
			AddressInfo(std::string host, int port);
			AddressInfo(int port);
			~AddressInfo();

			void			set(const sockaddr& addr, int len);

			std::string		getString();
			std::string     getStrAddr();
			int				getPort();

			const sockaddr&	getAddr() const;
			const size_t&	getAddrLen() const;

			bool operator == (int n);

		private:
			void	    getinfo(const char *host, const char *port);
			sockaddr	m_addr;
			size_t		m_len;
			int			m_port;
			std::string	m_saddr;
		};

	};	// end namespace net
};	//end namespace yuh