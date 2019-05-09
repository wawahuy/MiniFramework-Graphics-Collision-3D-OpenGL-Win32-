/*
	- SocketSelector.h
	- Network Selector!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	01/12/2018
	- Update	:
*/

#pragma once
#include "AddressInfo.h"

namespace yuh {
	namespace net {

		class NETWORK_API SocketSelector
		{
		public:
			SocketSelector();
			virtual ~SocketSelector();
		};

	};	// end namespace net
};	//end namespace yuh