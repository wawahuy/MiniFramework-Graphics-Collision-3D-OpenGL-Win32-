#include "WMenu.h"



namespace yuh {
	namespace window {

		WMenu::WMenu()
		{
			m_type = WINOBJ::NONE_OBJ;
			m_menu = CreateMenu();
		}


		WMenu::~WMenu()
		{
		}

		WMenuPtr WMenu::create()
		{
			return WMenuPtr(new WMenu());
		}

		void WMenu::append(WChildMenu & child)
		{
			//Save to list
			m_child.insert(OneChildMenu(child.m_id, child));

			//win32api
			child.m_menu = &m_menu;
			AppendMenu(m_menu, child.m_type, child.m_id, child.m_name.c_str());
		}

		void WMenu::append(const WMenuPtr_ & menu, const std::wstring& title)
		{
			//Menu -> ChildMenu In override
			WChildMenu child = *menu.get();
		
			//Title of popup
			child.m_name = (wchar_t*)title.c_str();

			//add child
			append(child);
		}

		const ListChildMenu & WMenu::getListChildMenu() const
		{
			return m_child;
		}


		void WMenu::onAppend(HWND *hwnd)
		{
			m_hwnd = hwnd;
			SetMenu(*hwnd, m_menu);
		}

		void WMenu::onRemove(HWND *hwnd)
		{
			//Destroy Child
			for (auto temp = m_child.begin(); temp != m_child.end(); temp++) {
				WChildMenu *child = &temp->second;
				RemoveMenu(m_menu, child->m_id, child->m_type);
			}

			//Destroy Menu
			DestroyMenu(m_menu);
		}


		WMenu::operator WChildMenu()
		{
			WChildMenu child;
			child.m_menu = &m_menu;
			child.m_name = L"None";
			child.m_type = MF_POPUP;
			child.m_id = (LONG_PTR)m_menu;
			return child;
		}


	}
}