/*
	- TCPSocket.cpp
	- Network TCP Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	27/11/2018
	- Update	:	01/12/2018
*/

#include "TCPSocket.h"


namespace yuh {
	namespace net {

		SP_TCPSocket TCPSocket::create()
		{
			return SP_TCPSocket(new TCPSocket());
		}

		TCPSocket::TCPSocket() : Socket(PROTOCOL::TCP)
		{
		}

		TCPSocket::TCPSocket(SOCKET & sock)
		{
			m_socket = sock;
		}

		TCPSocket::~TCPSocket()
		{
		}

		bool TCPSocket::connect(const AddressInfo& addr)
		{
			m_addrinfo = addr;
			int r = ::connect(m_socket, &m_addrinfo.getAddr(), m_addrinfo.getAddrLen());
			return r != SOCKET_ERROR;
		}

		bool TCPSocket::bind()
		{
			return ::bind(m_socket, &m_addrinfo.getAddr(), m_addrinfo.getAddrLen()) == 0;
		}

		bool TCPSocket::listen(int port)
		{
			return this->listen(port, SOMAXCONN);
		}

		bool TCPSocket::listen(int port, int backlog)
		{
			m_addrinfo = AddressInfo(port);
			bind();
			return ::listen(m_socket, backlog) == 0;
		}


		bool TCPSocket::accept(SP_TCPSocket &tcp)
		{
			sockaddr	addr;
			int			len = (int)sizeof(struct sockaddr);
			SOCKET		iResult = ::accept(m_socket, &addr, &len);

			if (iResult == INVALID_SOCKET) {
				return false;
			}

			TCPSocket	*sock = new TCPSocket(iResult);
			sock->m_addrinfo.set(addr, len);

			tcp = TCPSocketPtr(sock);

			return true;
		}

		AddressInfo TCPSocket::getAddress()
		{
			return m_addrinfo;
		}


		bool TCPSocket::send(const char * buffer, int lenbuffer)
		{
			return ::send(m_socket, buffer, lenbuffer, 0) == 0;
		}

		bool TCPSocket::send(Packet & packet)
		{
			return ::send(m_socket, packet.getData(), packet.getSize(), 0) == 0;
		}

		Socket::Status TCPSocket::recv(char *buffer, int &lenbuffer)
		{
			lenbuffer = ::recv(m_socket, buffer, lenbuffer, 0);

			if (lenbuffer > 0 && lenbuffer <= MAX_BUFFER) {
				return SK_OK;
			}
			else if (lenbuffer == 0) {
				return SK_DISCONNECTED;
			}

			return SK_ERROR;
		}

		Socket::Status TCPSocket::recv(Packet & packet)
		{
			char buffer[1024];
			std::size_t lenbuffer = MAX_BUFFER;

			lenbuffer = ::recv(m_socket, buffer, lenbuffer, 0);

			if (lenbuffer > 0 & lenbuffer <= MAX_BUFFER) {
				packet.append(buffer, lenbuffer);
				return SK_OK;
			}
			else if (lenbuffer == 0) {
				return SK_DISCONNECTED;
			}

			return SK_ERROR;
		}

	};	// end namespace net
};	//end namespace yuh