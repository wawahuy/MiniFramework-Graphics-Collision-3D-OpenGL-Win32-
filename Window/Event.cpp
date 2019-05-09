#include "Event.h"

bool yuh::window::Event::isGetEventW32API = false;

std::queue<MSG> yuh::window::Event::m_globalMsg;

bool yuh::window::Event::pollEvent(MSG & msg)
{
	if (m_globalMsg.empty()) return false;

	msg = m_globalMsg.front();

	m_globalMsg.pop();

	return true;
}


