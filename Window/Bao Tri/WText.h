#pragma once
#include "Window.h"
#include "WindowObject.h"

#define WTextPtr_ std::shared_ptr<WText>

namespace yuh {
	namespace window {

		/*
		 *
		 */
		class WINDOW_API WText : public WindowObject, public Window
		{
		public:
			~WText();

			static WTextPtr_ create(std::wstring str, Vec2i position, Vec2ui rect);
			
			void setTextAlign(ALIGN align);

			void setBorder(bool flag);

		protected:
			WText(std::wstring str, Vec2i position, Vec2ui rect);

		private:
			void onAppend(HWND *hwnd);
			void onRemove(HWND *hwnd);

			long m_align = SS_LEFT;
			bool m_border = false;
		};

		typedef std::shared_ptr<WText> WTextPtr;

	}	//end window
}	//end yuh

