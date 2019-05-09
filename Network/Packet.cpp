/*
	- Packet.cpp
	- Network Packet!
	- Project	:	Network Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	01/12/2018
	- Update	:
*/


#include "Packet.h"
#include <windows.h>

namespace yuh {
	namespace net {

		Packet::Packet()
		{
		}

		Packet::Packet(std::string str)
		{
			append(str);
		}

		Packet::Packet(byte * data, std::size_t size)
		{
			m_data.assign(data, data + size);
		}


		Packet::~Packet()
		{
		}

		void Packet::append(byte * data, std::size_t size)
		{
			std::size_t start = m_data.size();
			m_data.resize(start + size);
			std::memcpy(&m_data[start], data, size);
		}

		void Packet::append(Packet & packet)
		{
			append(&packet.m_data[0], packet.m_data.size());
		}

		void Packet::append(std::string str)
		{
			append(&str[0], str.size());
		}

		void Packet::append(std::wstring str)
		{
			if (str.empty()) return;
			int sz = WideCharToMultiByte(CP_UTF8, 0, &str[0], -1, 0, 0, 0, 0);
			std::string res(sz, 0);
			WideCharToMultiByte(CP_UTF8, 0, &str[0], -1, &res[0], sz, 0, 0);
			append(res);
		}

		void Packet::clear()
		{
			m_data.clear();
		}

		byte * Packet::getData()
		{
			return &m_data[0];
		}

		std::string Packet::getString()
		{
			return std::string(m_data.begin(), m_data.end());
		}

		std::wstring Packet::getWString()
		{
				if (m_data.empty()) return std::wstring();
				size_t charsNeeded = ::MultiByteToWideChar(CP_UTF8, 0, m_data.data(), (int)m_data.size(), NULL, 0);
				std::vector<wchar_t> buffer(charsNeeded);
				int charsConverted = ::MultiByteToWideChar(CP_UTF8, 0, m_data.data(), (int)m_data.size(), &buffer[0], buffer.size());
				return std::wstring(&buffer[0], charsConverted);
		}

		std::size_t Packet::getSize()
		{
			return m_data.size();
		}

	};	// end namespace net
};	//end namespace yuh