#include "WChildMenu.h"
#include "WindowObject.h"
#include "Event.h"

namespace yuh {
	namespace window {

		long WChildMenu::m_globalID = YUH_OBJ_ID_MENU_START;

		WChildMenu::WChildMenu()
		{
		}

		WChildMenu::WChildMenu(const std::wstring & name, MenuType type, void * userdata)
		{
			m_name = name;
			m_type = type;
			m_id = generalID();
			m_userdata = userdata;
		}

		void * WChildMenu::getUserData()
		{
			return m_userdata;
		}

		void WChildMenu::disableItem()
		{
			EnableMenuItem(*m_menu, m_id, MF_DISABLED);
		}

		void WChildMenu::enableItem()
		{
			EnableMenuItem(*m_menu, m_id, MF_ENABLED);
		}


		void WChildMenu::checkItem()
		{
			CheckMenuItem(*m_menu, m_id, MF_UNCHECKED);
		}

		void WChildMenu::unCheckItem()
		{
			CheckMenuItem(*m_menu, m_id, MF_CHECKED);
		}

		WChildMenu::operator long()
		{
			return m_id;
		}

		long WChildMenu::generalID()
		{
			if (m_globalID > YUH_OBJ_ID_MENU_END) {
				std::cout << "Error general ID Menu!" << std::endl;
				return -1;
			}
			return m_globalID++;
		}
	}
}