#include "WText.h"

namespace yuh {
	namespace window {


		WText::WText(std::wstring str, Vec2i position, Vec2ui rect) :
		Window(L"Static", str, NULL, position, rect, NULL, NULL, NULL, NULL)
		{
		}

		void WText::onAppend(HWND *hwnd)
		{
			SetParent(m_window, *hwnd);
			setStyle(WS_VISIBLE | WS_CHILD | m_align |( m_border ? WS_BORDER : 0));
		}

		void WText::onRemove(HWND *hwnd)
		{
			DestroyWindow(m_window);
		}

		WText::~WText()
		{
		}

		WTextPtr_ WText::create(std::wstring str, Vec2i position, Vec2ui rect)
		{
			return WTextPtr(new WText(str, position, rect));
		}

		void WText::setTextAlign(ALIGN align)
		{
			m_align = align;
			setStyle(WS_VISIBLE | WS_CHILD | m_align | (m_border ? WS_BORDER : 0));
		}

		void WText::setBorder(bool flag)
		{
			m_border = flag;
			setStyle(WS_VISIBLE | WS_CHILD | m_align | (m_border ? WS_BORDER : 0));
		}

	}
}