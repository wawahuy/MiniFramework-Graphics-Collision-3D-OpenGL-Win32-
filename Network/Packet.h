/*
	- Packet.h
	- Network Packet!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	01/12/2018
	- Update	:	05/12/2018
*/

#pragma once
#include <memory>
#include <vector>
#include <string>
typedef char byte;

#include "Export.h"

namespace yuh {
	namespace net {

		class NETWORK_API Packet
		{
		public:
			Packet();
			Packet(std::string str);
			Packet(byte *data, std::size_t size);
			~Packet();

			/* Thêm dữ liệu cho packet
			 * @data: dữ liệu cần truyền vào, chú ý là mãng byte
			 * @size: số byte
			 */
			void append(byte *data, std::size_t size);


			/* Thêm dữ liệu cho packet
			 */
			void append(Packet &packet);


			/* Thêm dữ liệu cho packet
			 */
			void append(std::string str);

			
			/* Thêm dữ liệu cho packet
			 */
			void append(std::wstring str);


			/* Xóa vùng nhớ
			 */
			void clear();

			/* Con trỏ đến byte đầu  tiên của dữ liệu
			 * Nó tương đương với char
			 *
			 */
			byte*		getData();


			/* Hiện thị dưới dạng văn bản
			 */
			std::string getString();
			std::wstring getWString();


			/* Kích thước gói tin
			 * Tính theo byte
			 */
			std::size_t getSize();


		private:
			std::vector<char> m_data;
		};

	};	// end namespace net
};	//end namespace yuh