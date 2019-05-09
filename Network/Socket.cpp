/*
	- Socket.cpp
	- Network Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	01/12/2018
	- Update	:
*/



#include "Socket.h"

namespace yuh {
	namespace net {

		Socket::Socket() :
			m_socket(INVALID_SOCKET),
			m_block(true)
		{
		}

		Socket::Socket(PROTOCOL protocol) :
			m_socket(INVALID_SOCKET),
			m_block(true)
		{
			m_socket = socket(AF_INET,
				protocol == UDP ? SOCK_DGRAM : SOCK_STREAM,
				protocol);
		}

		std::shared_ptr<Socket> Socket::create(PROTOCOL proto)
		{
			return std::shared_ptr<Socket>(new Socket(proto));
		}

		Socket::~Socket()
		{
			close();
		}


		void Socket::close()
		{
			setBlocking(true);
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
		}

		bool Socket::isClose()
		{
			return m_socket == INVALID_SOCKET;
		}

		void Socket::setBlocking(bool blocking)
		{
			m_block = blocking;
			u_long arg = blocking ? 0 : 1;
			int result = ioctlsocket(m_socket, FIONBIO, &arg);

			if (result != 0) {
				std::cerr << "Setup non - blocking is error!";
			}
		}

		bool Socket::isBlocking()
		{
			return m_block;
		}

		SOCKET Socket::getHandle()
		{
			return m_socket;
		}


		AddressInfo Socket::getSocketInfo()
		{
			sockaddr	 addr;
			ZeroMemory(&addr, sizeof(addr));
			int			 len = sizeof(struct sockaddr);
			len = getsockname(m_socket, &addr, &len);

			AddressInfo addrinfo;
			addrinfo.set(addr, len);

			return addrinfo;
		}


		//Start WSA
		struct init {
			init()
			{
				std::cout << "YUH Establish Network!" << std::endl;
				WSADATA wsadata;
				if (::WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
					std::cout << "Start up is error Winsock!";
				}
			}

			~init()
			{
				std::cout << "YUH Close Network!" << std::endl;
				::WSACleanup();
			}
		} _init_;

	};	// end namespace net
};	//end namespace yuh