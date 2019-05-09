#include "WEdit.h"

namespace yuh {
	namespace window {

		long WEdit::m_generalID = YUH_OBJ_ID_EDIT_START;

		long WEdit::generalID()
		{
			return m_generalID++;
		}

		WEdit::WEdit(std::wstring str, Vec2i position, Vec2ui rect, EditType type) :
			m_str(str),
			m_position(position),
			m_rect(rect),
			m_typeedit(type)
		{
		}

		long WEdit::updateStyle()
		{
			return
				WS_CHILD | WS_VISIBLE | m_align | m_typeedit |
				(m_readonly ? ES_READONLY : 0) |
				(m_scroll ? WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL : 0) |
				(m_border ? WS_BORDER : 0) |
				(m_multiline ? ES_MULTILINE : 0) ;
		}

		void WEdit::onAppend(HWND *hwnd)
		{
			if (isOpen()) {
				std::cout << "Dont append 2 Window!";
				return;
			}

			createWindow(L"Edit", L"", updateStyle(), m_position, m_rect, (HMENU)generalID(), *hwnd, NULL, NULL);
		}
		
		void WEdit::onRemove(HWND *hwnd)
		{
			DestroyWindow(m_window);
		}

		WEdit::~WEdit()
		{
		}

		WEditPtr_ WEdit::create(std::wstring str, Vec2i position, Vec2ui rect, EditType type)
		{
			return WEditPtr(new WEdit(str, position, rect, type));
		}

		void WEdit::setTextAlign(ALIGN align)
		{
			m_align = align;
			setStyle(updateStyle());
		}

		void WEdit::setBorder(bool flag)
		{
			m_border = flag;
			setStyle(updateStyle());
		}

		void WEdit::setScroll(bool flag)
		{
			m_scroll = flag;
			setStyle(updateStyle());
		}

		void WEdit::setMultiLine(bool flag)
		{
			m_multiline = flag;
			setStyle(updateStyle());
		}

		void WEdit::setType(EditType type)
		{
			m_typeedit = type;
		}

		void WEdit::setReadyOnly(bool flag)
		{
			m_readonly = flag;
		}

		std::wstring WEdit::getText()
		{
			return getTitle();
		}

		void WEdit::setText(const std::wstring & str)
		{
			setTitile(str);
		}

	}
}