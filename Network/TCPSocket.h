/*
	- TCPSocket.h
	- Network TCP Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	27/11/2018
	- Update	:	01/12/2018
*/

#pragma once
#include "Socket.h"
#define SP_TCPSocket std::shared_ptr<TCPSocket>

namespace yuh {
	namespace net {

		class NETWORK_API TCPSocket : public Socket
		{
		public:
			static SP_TCPSocket create();
			virtual ~TCPSocket();
			bool		 connect(const AddressInfo& info);
			bool		 listen(int port);
			bool		 listen(int port, int backlog);
			bool		 send(const char *buffer, int lenbuffer);
			bool		 send(Packet& packet);
			Status		 recv(char *buffer, int &lenbuffer);
			Status 		 recv(Packet& packet);
			bool		 accept(SP_TCPSocket &tcp);
			AddressInfo  getAddress();

		protected:
			TCPSocket();
			TCPSocket(SOCKET &sock);

		private:
			bool		bind();
			AddressInfo m_addrinfo;
		};


		/* smart pointer
		 * use with TCPSocket::create()
		 */
		typedef std::shared_ptr<TCPSocket> TCPSocketPtr;


	};	// end namespace net
};	//end namespace yuh

/* Example
 #
 # --- Create Socket TCP -----
 #  yuh::net::TCPSocketPtr tcp = yuh::net::TCPSocket::create();
 #
 # ======== SERVER =====================
 #
 # --- Bind, Listen ---
 #  tcp->listen(8080);
 #
 # --- Accept -> New TCPSocketPtr ----
 #	TCPSocketPtr client;
 #  bool status = tcp->accept(client);
 #
 # --- Send, Recv ----
 #  yuh::net::Packet packet;
 #  Socket::Status status = tcp->recv(packet);
 #
 #
 # ======== CLIENT =====================
 #  tcp->connect(AddressInfo('192.168.1.250', 8080)
 #  
 #
 */