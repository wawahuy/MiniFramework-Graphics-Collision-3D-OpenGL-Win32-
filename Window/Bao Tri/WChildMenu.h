/*
	- ChildMenu.h
	- Project	:	Window Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	06/12/2018
	- Update	:
	- Deltail	:	ChildMenu in WMenu
*/

#pragma once
#include "Export.h"
#include <Windows.h>
#include <string>
#include <System/NonCopyable.h>
#include <map>

namespace yuh {
	namespace window {

		/* Menu Type On Child
		 * 
		 */
		enum MenuType {
			STRING = MF_STRING,
			LINE = MF_SEPARATOR,
			DISABLE = MF_DISABLED,
			ENABLE = MF_ENABLED,
			CHECKED = MF_CHECKED,
			UNCHECKED = MF_UNCHECKED

		};

		/* Menu child
		 * Allow copy multi object
		 * Delete when use remove of Menu Class
		 *
		 */
		class WINDOW_API WChildMenu {
			friend class WMenu;

		public:
			WChildMenu();

			WChildMenu(const std::wstring &name, MenuType type = MenuType::STRING, void * userdata = NULL);


			void *getUserData();


			/* Support MenuType: DISABLE
			 *
			 */
			void disableItem();
			void enableItem();


			/* Support Menu Type: CHECKED
			 *
			 */
			void checkItem();
			void unCheckItem();


			/* Get ID Object
			 */
			operator long();

		private:
			long			m_id;
			long			m_type;
			std::wstring	m_name;
			void		   *m_userdata;
			HMENU		   *m_menu;

			static long m_globalID;
			static long generalID();
		};

		typedef std::map<long, WChildMenu> ListChildMenu;
		typedef std::pair<long, WChildMenu> OneChildMenu;

	}
}