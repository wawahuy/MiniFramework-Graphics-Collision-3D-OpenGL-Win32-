#pragma once
#include "Window.h"
#include "WindowObject.h"

#define WEditPtr_ std::shared_ptr<WEdit>

namespace yuh {
	namespace window {

		enum EditType {
			PASSWORD = ES_PASSWORD,
			NUMBER = ES_NUMBER,
			TEXT = 0,
			TEXT_UPPER = ES_UPPERCASE,
			TEXT_LOWER = ES_LOWERCASE
		};

		/*
		 *
		 */
		class WINDOW_API WEdit : public WindowObject, public Window
		{
		public:
			~WEdit();

			static WEditPtr_ create(std::wstring str, Vec2i position, Vec2ui rect, EditType type = TEXT);
			
			void setTextAlign(ALIGN align);

			void setBorder(bool flag);

			void setScroll(bool flag);

			void setMultiLine(bool flag);

			void setType(EditType type);

			void setReadyOnly(bool flag = true);

			std::wstring getText();

			void setText(const std::wstring &str);

		protected:
			WEdit(std::wstring str, Vec2i position, Vec2ui rect, EditType type = TEXT);

		private:
			long updateStyle();
			void onAppend(HWND *hwnd);
			void onRemove(HWND *hwnd);

			long m_align = SS_LEFT;
			bool m_border = false;
			bool m_scroll = false;
			bool m_multiline = false;
			bool m_readonly = false;

			std::wstring m_str;
			Vec2i		 m_position;
			Vec2ui		 m_rect;
			EditType	 m_typeedit;

			//General ID
			static long m_generalID;
			static long generalID();
		};

		typedef std::shared_ptr<WEdit> WEditPtr;

	}	//end window
}	//end yuh

