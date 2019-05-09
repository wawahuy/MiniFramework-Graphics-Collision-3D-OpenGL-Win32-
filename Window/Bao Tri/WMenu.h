/*
	- WMenu.h
	- Project	:	Window Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	06/12/2018
	- Update	:
	- Deltail	:	WMenu
*/

#pragma once
#include "WindowObject.h"
#include "WChildMenu.h"
#include <System/NonCopyable.h>

#define WMenuPtr_ std::shared_ptr<WMenu>

namespace yuh {
	namespace window {

		/*  Create Menu
		 *  Type: WMenuPtr
		 *	Use : WMenu::create(...)
		 *  EX:
		 *		WMenuPtr menu = WMenu::create()
		 *
		 */
		class WINDOW_API WMenu : public WindowObject, NonCopyable
		{
			friend class Window;

		public:
			virtual ~WMenu();

			/* Create Smart Pointer Menu
			 *  
			 */
			static WMenuPtr_ create();

			
			/* Add list
			 *
			 */
			void append(WChildMenu &child);


			/* Add sub-menu
			 *
			 */
			void append(const WMenuPtr_ &child, const std::wstring& title);


			/* Get List Child Menu
			 *
			 */
			const ListChildMenu& getListChildMenu() const;


			
			/* Override
			 * Convert Menu to Child Menu
			 *
			 */
			operator WChildMenu();




		protected:
			WMenu();

		private:
			void onAppend(HWND *hwnd);
			void onRemove(HWND *hwnd);

			HMENU m_menu;
			HWND* m_hwnd;
			ListChildMenu m_child;
		};

		/* Container Smart Pointer Window
		 * Ex:
		 *		WMenuPtr menu = WMenuPtr::create(...)
		 */
		typedef std::shared_ptr<WMenu> WMenuPtr;

	} //end window
} //end yuh