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

#include "AddressInfo.h"
#include "Socket.h"

namespace yuh {
	namespace net {

		AddressInfo::AddressInfo()
		{
		}

		AddressInfo::AddressInfo(std::string host, int port) : m_saddr(host), m_port(port)
		{
			getinfo(host.c_str(), std::to_string(port).c_str());
		}

		AddressInfo::AddressInfo(int port) : m_saddr("0.0.0.0"), m_port(port)
		{
			getinfo(NULL, std::to_string(port).c_str());
		}

		AddressInfo::~AddressInfo()
		{
		}


		void AddressInfo::set(const sockaddr & addr, int len)
		{
			m_addr = addr;
			m_len = len;

			//addr binary to string
			char host[255];
			char port[10];
			getnameinfo(&m_addr, sizeof(m_addr), host, sizeof(host), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV);
			m_saddr = std::string(host);
			m_port = std::stoi(std::string(port));
		}

		std::string AddressInfo::getString()
		{
			return std::string(m_saddr) + ":" + std::to_string(m_port);
		}

		std::string AddressInfo::getStrAddr()
		{

			return m_saddr;
		}

		int AddressInfo::getPort()
		{
			return m_port;
		}

		const sockaddr & AddressInfo::getAddr() const
		{
			return m_addr;
		}

		const size_t & AddressInfo::getAddrLen() const
		{
			return m_len;
		}

		bool AddressInfo::operator==(int n)
		{
			return m_saddr.size() == 0;
		}

		void AddressInfo::getinfo(const char * host, const char * port)
		{
			addrinfo hints;
			addrinfo *result, *r;

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_INET;
			hints.ai_flags = AI_PASSIVE;

			int iResult = getaddrinfo(
				host,
				port,
				&hints, &result);

			if (iResult != 0) {
				std::cerr << "Get information address is error! Code: " << iResult << std::endl;
			}

			r = result;
			m_addr = *r->ai_addr;
			m_len = r->ai_addrlen;

			freeaddrinfo(result);
		}

	};	// end namespace net
};	//end namespace yuh