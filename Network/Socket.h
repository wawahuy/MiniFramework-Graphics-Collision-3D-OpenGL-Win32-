/*
	- Socket.h
	- Network Winsock!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	01/12/2018
	- Update	:	
*/


#pragma once
#include "AddressInfo.h"
#include "Packet.h"
#include <System/NonCopyable.h>

#define MAX_BUFFER 1024

enum PROTOCOL {
	TCP = IPPROTO_TCP, 
	UDP = IPPROTO_UDP
};

namespace yuh {
	namespace net {

		/* Socket
		 * Use SocketPtr type and ::create()
		 */
		class NETWORK_API Socket : public NonCopyable
		{
		public:
			enum Status {
				SK_OK,
				SK_ERROR,
				SK_DISCONNECTED,
				SK_WAIT
			};

			virtual ~Socket();


			/* Socket
			 * @proto: UDP / TCP
			 * @return: SocketPtr
			 */
			static std::shared_ptr<Socket> create(PROTOCOL proto);



			/* Close socket
			 *
			 */
			void		 close();


			/* Socket Is Error
			 *
			 * @return: true - error, false - active
			 */
			bool		 isClose();


			/* Blocking
			 *
			 */
			void		setBlocking(bool blocking);


			/* Is Block or Non
			 *
			 * @return: true - block, false - non
			 */
			bool		isBlocking();


			/* Handle Socket
			 * Winsock API
			 *
			 * @return: SOCKET ID
			 */
			SOCKET		getHandle();


			/* Info Socket
			 *
			 */
			AddressInfo getSocketInfo();


		protected:
			Socket();
			Socket(PROTOCOL protocol);

			SOCKET		m_socket;
			bool		m_block;
			PROTOCOL	m_proto;
		};


		/* Pointer Socket, Shared_Ptr
		 * Use Socket::create(protocol)
		 */
		typedef std::shared_ptr<Socket> SocketPtr;
	
	};	// end namespace net
};	//end namespace yuh


/*	Example
	#
	# --- Create Socket ---------
	#
	#  yuh::net::SocketPtr sock = yuh::net::Socket::create(UDP);
	#
	# --- Non - blocking --------
	#  
	#  sock->setBlocking(false);
	#
	# --- Get Address Socket ----
	#
	#  yuh::net::AddressInfo info = sock->getSocketInfo();
	#
*/