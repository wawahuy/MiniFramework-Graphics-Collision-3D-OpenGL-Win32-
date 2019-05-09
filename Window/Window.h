/*
	- Window.h
	- Project	:	Window Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	05/12/2018
	- Update	:
	- Deltail	:	Win32API Window
*/


#pragma once
#include "Export.h"
#include "Event.h"
#include "WglContext.h"
#include <iostream>
#include <string>
#include <memory>
#include <queue>
#include <Windows.h>
#include <Math/Vector2D.h>
#include <System/NonCopyable.h>
#include <System/Timer.h>

//Free console on VISUAL STUDIO
#ifdef YUH_FREE_CONSOLE
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#define WindowPtr_ std::shared_ptr<Window>

namespace yuh {
	namespace window {

		enum ALIGN {
			LEFT = SS_LEFT,
			RIGHT = SS_RIGHT,
			CENTER = SS_CENTER
		};

		const wchar_t wndClassName[] = L"YUH_WINDOW";		//Name WND Class

		/* Create New Window
		 * Only support create with smart pointer 
		 * Type: WindowPtr
		 * Create: Window::create(....)
		 * EX:
		 *		WindowPtr window = Window::create()
		 *
		 */
		class WINDOW_API Window : public NonCopyable, public WglContext
		{
		public:
			virtual ~Window();

			static LRESULT CALLBACK globalEvent(HWND hwnd, UINT cmd, WPARAM wparam, LPARAM lparam);


			/* Create New Window
			 * @name:	title window, see on bar
			 * @size:	size window
			 * @style:	style window, use WS_[..], support |
			 *
			 */
			static WindowPtr_ create(const std::wstring& name, Vec2ui size, const ContextSetting &setting, long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE);


			/* Create New Window
			* @name:		title window, see on bar
			* @winparent:	window parent
			* @size:		size window
			* @style:		style window, use WS_[..], support |
			*
			*/
			static WindowPtr_ create(const std::wstring& name, Vec2ui size, const WindowPtr_& windowParent, const ContextSetting &setting, long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE);


			/* Hide cursor
			 *
			 */
			static void hideWindowCursor(bool cursor);


			/*	Get Event in window
			 *	Non-blocking
			 *		
			 */
			bool pollEvent(Event &evt);



			/* Get Event in window
			 * Blocking
			 *
			 */
			void waitEvent(Event &evt);


			/* Display Window OpenGL
			 * Limit frame
			 * SwapBuffer
			 *
			 */
			void display();


			/* Limit frame/s
			 *
			 */
			void setFrameMax(unsigned int frame);


			/* Close window
			 *
			 */
			void close();


			/* Status onpen window
			 *
			 */
			bool isOpen();


			/* Get HWND in Win32API
			 * 
			 */
			HWND getHandle();


			/* Set Parent of window
			 *
			 */
			void setParent(const WindowPtr_ window);
			void setParent(Window* window);

			HWND getParent();


			/* Set/Get mouse
			 *
			 */
			void  setMousePosition(const Vec2i& position);
			Vec2i getMousePosition();

			void  setMouseCenterWindow();
			Vec2i getMouseCenterWindow();
			bool  isMouseCenterWindow();
			
			/* Set Get
			 *
			 */
			void  setPosition(Vec2i position);
			void  setSize(Vec2ui size);
			void  setTitile(const std::wstring &title);
			void  setStyle(long style);
			WglContext*  getContext();


			Vec2i		 getPosition();
			Vec2ui		 getSize();
			std::wstring getTitle();
			long		 getStyle();

			//Change Type
			operator HWND();

			Window();

			Window(const std::wstring& name, Vec2ui size, const ContextSetting& setting, long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE);

			Window(const std::wstring& name, Vec2ui size, const WindowPtr_& winParent, const ContextSetting& setting, long style = WS_OVERLAPPEDWINDOW | WS_VISIBLE);

			Window(std::wstring wndClassName, std::wstring name, long style, Vec2i position, Vec2ui size, HMENU hmenu, HWND parent, HINSTANCE hInstance, void *lparam, const ContextSetting& setting);


		protected:
			
			void createWindow(std::wstring wndClassName, std::wstring name, long style, Vec2i position, Vec2ui size, HMENU hmenu, HWND parent, HINSTANCE hInstance, void *lparam, const ContextSetting& setting);

			HWND	m_window;


		private:
			long GetEvent(UINT cmd, WPARAM wparam, LPARAM lparam);

			//window
			bool				m_open;
			Vec2ui				m_size;
			Vec2i				m_position;
			HWND				m_windowParent;

			Vec2i				m_centerMouse;

			//Event
			std::queue<Event>   m_event;

			//frame limit
			unsigned int		m_maxFrame;
			unsigned int		m_oneFrame;
			Timer				m_timerFrame;

		};


		/* Container Smart Pointer Window
		 * Ex:
		 *		WindowPtr window = Window::create(...)
		 */
		typedef std::shared_ptr<Window> WindowPtr;



	}	//end window
}	//end yuh
