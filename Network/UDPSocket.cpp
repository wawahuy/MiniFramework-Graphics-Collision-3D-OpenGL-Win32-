/*
	- UDPSocket.cpp
	- Network UDP Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	27/11/2018
	- Update	:
*/


#include "UDPSocket.h"

namespace yuh {
	namespace net {

		std::shared_ptr<UDPSocket> UDPSocket::create()
		{
			return UDPSocketPtr(new UDPSocket());
		}

		UDPSocket::UDPSocket() : Socket(PROTOCOL::UDP)
		{
		}


		UDPSocket::~UDPSocket()
		{
		}

		bool UDPSocket::bind(int port)
		{
			m_addressinfo = AddressInfo(port);
			return ::bind(m_socket, &m_addressinfo.getAddr(), m_addressinfo.getAddrLen()) == 0;
		}


		bool UDPSocket::sendto(void * buffer, int len, const AddressInfo & toAddr)
		{
			int iResult = ::sendto(m_socket,
				static_cast<const char *>(buffer),
				len,
				0,
				&toAddr.getAddr(),
				toAddr.getAddrLen());
			return iResult != SOCKET_ERROR;
		}


		bool UDPSocket::sendto(Packet & packet, const AddressInfo & toAddr)
		{
			int iResult = ::sendto(m_socket,
				packet.getData(),
				packet.getSize(),
				0,
				&toAddr.getAddr(),
				toAddr.getAddrLen());
			return iResult != SOCKET_ERROR;
		}


		Socket::Status UDPSocket::recvfrom(void * buffer, int &len)
		{
			len = ::recvfrom(m_socket, static_cast<char *>(buffer), len, 0, NULL, NULL);

			if (len > 0) return SK_OK;
			else if (len == 0) return SK_DISCONNECTED;
			return SK_ERROR;
		}


		Socket::Status UDPSocket::recvfrom(Packet & packet)
		{
			char buffer[1024];
			std::size_t len = 1024;
			len = ::recvfrom(m_socket, static_cast<char *>(buffer), len, 0, NULL, NULL);

			if (len > 0 && len < 1025) {
				packet.append(buffer, len);
				return SK_OK;
			}
			else if (len == 0) {
				return SK_DISCONNECTED;
			}

			return SK_ERROR;
		}

		Socket::Status UDPSocket::recvfrom(void * buffer, int &len, AddressInfo & fromAddr)
		{
			sockaddr addr;
			int fromlen = (int)sizeof(struct sockaddr);
			len = ::recvfrom(m_socket,
				static_cast<char *>(buffer),
				len,
				0,
				&addr,
				&fromlen);
			fromAddr.set(addr, sizeof(addr));

			if (len > 0) return SK_OK;
			else if (len == 0) return SK_DISCONNECTED;
			return SK_ERROR;
		}

		Socket::Status UDPSocket::recvfrom(Packet & packet, AddressInfo & fromAddr)
		{
			char buffer[1024];
			std::size_t len = 1024;
			sockaddr addr;
			int fromlen = (int)sizeof(struct sockaddr);

			len = ::recvfrom(m_socket,
				static_cast<char *>(buffer),
				len,
				0,
				&addr,
				&fromlen);

			if (len > 0 && len < 1025) {
				packet.append(buffer, len);
				fromAddr.set(addr, sizeof(addr));
				return SK_OK;
			}
			else if (len == 0) {
				return SK_DISCONNECTED;
			}

			return SK_ERROR;
		}

		AddressInfo UDPSocket::getAddress()
		{
			return m_addressinfo;
		}

	};	// end namespace net
};	//end namespace yuh