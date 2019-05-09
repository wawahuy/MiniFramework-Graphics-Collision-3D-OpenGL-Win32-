/*
	- UDPSocket.h
	- Network UDP Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	27/11/2018
	- Update	:
*/

#pragma once
#include "Socket.h"

namespace yuh {
	namespace net {

		class NETWORK_API UDPSocket : public Socket
		{
		public:
			static std::shared_ptr<UDPSocket> create();
			virtual ~UDPSocket();
			bool bind(int port);

			bool sendto(void *buffer, int len, const AddressInfo &toAddr);
			bool sendto(Packet &packet, const AddressInfo &toAddr);

			Status  recvfrom(void *buffer, int &len);
			Status  recvfrom(Packet &packet);
			Status  recvfrom(void *buffer, int &len, AddressInfo &fromAddr);
			Status  recvfrom(Packet &packet, AddressInfo &fromAddr);

			AddressInfo  getAddress();


		private:
			UDPSocket();
			AddressInfo m_addressinfo;
		};

		typedef std::shared_ptr<UDPSocket> UDPSocketPtr;

	};	// end namespace net
};	//end namespace yuh

/*	Example
	#
	# --- Create Socket UDP -----
	#  UDPSocketPtr udp = UDPSocket::create();
	#
	# ======== Bind =====================
	#
	#  udp->bind(0)		//Port duoc tao ngau nhien
	#
	#  udp->bind(8080)	//Nhan goi tin qua cong 8080
	#
	# ======== Send, Recv ===============
	#
	#  Packet packet;
	#
	#  udp->recvfrom(packet, addrClient);
	#
	#  udp->sendto(packet, addrClient);
	#
	#
*/