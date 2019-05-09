#include "Window.h"
//#include "WMenu.h"

namespace yuh {
	namespace window {

		bool	 setup_glew = false;				//Init glew

		WindowPtr Window::create(const std::wstring& name, Vec2ui size, const ContextSetting& setting, long style)
		{
			return std::shared_ptr<Window>(new Window(name, size, setting, style));
		}

		WindowPtr Window::create(const std::wstring & name, Vec2ui size, const WindowPtr_ & windowParent, const ContextSetting& setting, long style)
		{
			return std::shared_ptr<Window>(new Window(name, size, windowParent, setting, style));
		}

		void Window::hideWindowCursor(bool cursor)
		{
			ShowCursor(cursor);
		}

		bool Window::pollEvent(Event & evt)
		{

			/* Win32API
			* Peek message
			*
			*/
			MSG msg;
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageW(&msg);
			}


			// Check when no event
			if (m_event.size() == 0) return false;

			// Get event
			evt = m_event.front();

			// Pop event
			m_event.pop();

			return true;
		}


		void Window::waitEvent(Event &evt)
		{

			/* Win32API
			 * Wait message, accept when m_event of YUH
			 *
			 */
			do {
				MSG msg;
				GetMessage(&msg, 0, 0, 0);
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			while (m_event.size() == 0);

			// Get event
			evt = m_event.front();

			// Pop event
			m_event.pop();

		}

		void Window::display()
		{
			swapBufferGL();

			if (m_maxFrame != 0) {
				long timeOfOneFrame = m_timerFrame.elapsed();

				//Sleep with free time of 1 frame
				if (m_oneFrame > timeOfOneFrame) {
					Sleep(m_oneFrame - timeOfOneFrame);
				}

				//Reset time with 1 frame
				m_timerFrame.reset();
			}
		}

		void Window::setFrameMax(unsigned int frame)
		{
			m_maxFrame = frame;
			m_oneFrame = 1000 / frame;
			m_timerFrame.reset();
		}


		void Window::close()
		{
			if (m_open == false) return;
			m_open = false;
			closeGL();
			DestroyWindow(m_window);
		}

		bool Window::isOpen()
		{
			return m_open;
		}

		HWND Window::getHandle()
		{
			return m_window;
		}

		void Window::setParent(const WindowPtr_ window)
		{
			SetParent(m_window, window->m_window);
		}

		void Window::setParent(Window * window)
		{
			SetParent(m_window, window->m_window);
		}

		HWND Window::getParent()
		{
			return GetParent(m_window);;
		}

		void Window::setMousePosition(const Vec2i & position)
		{
			Vec2i v = getPosition() + position;
			SetCursorPos(v.x, v.y);
		}

		Vec2i Window::getMousePosition()
		{
			POINT pt;
			GetCursorPos(&pt);
			return Vec2i(pt.x, pt.y) - getPosition();
		}

		void Window::setMouseCenterWindow()
		{
			Vec2i halfSize(m_size.x / 2, m_size.y / 2);
			this->setMousePosition(halfSize);
		}

		Vec2i Window::getMouseCenterWindow()
		{
			return m_centerMouse;
		}

		bool Window::isMouseCenterWindow()
		{
			return getMousePosition() == m_centerMouse;
		}

		void Window::setPosition(Vec2i position)
		{
			SetWindowPos(m_window, NULL, position.x, position.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
		}

		void Window::setSize(Vec2ui size)
		{
			MessageBoxA(m_window, "ERROR!", "ERROR CHANG SIZE WINDOW!", 0);

			/*RECT rect;
			GetWindowRect(m_window, &rect);
			MapWindowPoints(HWND_DESKTOP, GetParent(m_window), (LPPOINT)&rect, 2);
			rect.bottom = rect.top + size.x;
			rect.right  = rect.left + size.y;
			SetWindowPos(m_window, NULL, 0, 0, rect.right, rect.bottom, SWP_NOMOVE | SWP_NOZORDER);*/
		}

		void Window::setTitile(const std::wstring & title)
		{
			SetWindowText(m_window, title.c_str());
		}

		void Window::setStyle(long style)
		{
			SetWindowLongPtr(m_window, GWL_STYLE, style);
		}

		WglContext * Window::getContext()
		{
			return (WglContext*)this;
		}

		Vec2i Window::getPosition()
		{
			RECT rect;
			GetWindowRect(m_window, &rect);
			MapWindowPoints(HWND_DESKTOP, GetParent(m_window), (LPPOINT)&rect, 2);
			return Vec2i(rect.left, rect.top);
		}

		Vec2ui Window::getSize()
		{
			RECT rect;
			GetWindowRect(m_window, &rect);
			MapWindowPoints(HWND_DESKTOP, GetParent(m_window), (LPPOINT)&rect, 2);

			Vec2ui size;
			size.x = rect.right - rect.left;
			size.y = rect.bottom - rect.top;
			return size;
		}

		std::wstring Window::getTitle()
		{
			wchar_t text[5000];
			GetWindowText(m_window, text, 5000);
			return std::wstring(text);
		}

		long Window::getStyle()
		{
			return GetWindowLongPtr(m_window, GWL_STYLE);
		}

		Window::operator HWND()
		{
			return m_window;
		}

		Window::Window() :
		m_open(false),
		m_window(NULL)
		{
		}

		Window::Window(const std::wstring& name, Vec2ui size, const ContextSetting& setting, long style) :
		m_open(false),
		m_size(size),
		m_maxFrame(0),
		m_position(CW_USEDEFAULT, CW_USEDEFAULT)
		{
			createWindow(wndClassName, name.c_str(), style, Vec2i(CW_USEDEFAULT, CW_USEDEFAULT), size, 0, 0, GetModuleHandle(0), this, setting);
		}

		Window::Window(const std::wstring & name, Vec2ui size, const WindowPtr_& winParent, const ContextSetting& setting, long style):
		m_open(false),
		m_size(size),
		m_maxFrame(0),
		m_position(CW_USEDEFAULT, CW_USEDEFAULT)
		{
			createWindow(wndClassName, name.c_str(), style, Vec2i(CW_USEDEFAULT, CW_USEDEFAULT), size, 0, winParent->m_window, GetModuleHandle(0), this, setting);
		}

		Window::Window(std::wstring wndClassName, std::wstring name, long style, Vec2i position, Vec2ui size, HMENU hmenu, HWND parent, HINSTANCE hInstance, void* lparam, const ContextSetting& setting) :
		m_open(false),
		m_size(size),
		m_maxFrame(0),
		m_position(CW_USEDEFAULT, CW_USEDEFAULT)
		{
			createWindow(wndClassName, name, style, position, size, hmenu, parent, hInstance, lparam, setting);
		}


		void Window::createWindow(std::wstring wndClassName, std::wstring name, long style, Vec2i position, Vec2ui size, HMENU hmenu, HWND parent, HINSTANCE hInstance, void * lparam, const ContextSetting& setting)
		{
			m_window = CreateWindowW(wndClassName.c_str(), name.c_str(), style, position.x, position.y, size.x, size.y, parent, hmenu, hInstance, lparam);

			if (m_window == NULL) {
				std::cout << "Error create window!" << std::endl;
				return;
			}

			ShowWindow(m_window, SW_SHOW);

			setGLWindow(m_window, setting);

			// Get center position!
			// @@
			m_size = size;
			setMouseCenterWindow();
			m_centerMouse = getMousePosition();
			while(!m_event.empty()) m_event.pop();

			m_open = true;
		}

		long Window::GetEvent(UINT cmd, WPARAM wparam, LPARAM lparam)
		{
			Event evt;
			evt.mouse.x = LOWORD(lparam);
			evt.mouse.y = HIWORD(lparam);

			switch (cmd) {

			/* Change size window
			 *
			 */
			case WM_SIZE:
				evt.type = Event::Type::Resize;
				break;

			/* mouse move window
			 */
			case WM_MOUSEMOVE:
				evt.type = Event::Type::MouseMove;
				evt.mouse = getMousePosition();
				break;

			case WM_KEYDOWN:
				evt.type = Event::Type::KEY_PRESSED;
				evt.key = wparam;
				break;

			case WM_KEYUP:
				evt.type = Event::Type::KEY_RELEASE;
				evt.key = wparam;
				break;

			default:
				return DefWindowProc(m_window, cmd, wparam, lparam);
			}

			/* Push event in queue
			 */
			m_event.push(evt);

			return 0;
		}



		Window::~Window()
		{
			close();
		}

		LRESULT CALLBACK Window::globalEvent(HWND hwnd, UINT cmd, WPARAM wparam, LPARAM lparam)
		{
			//Global Event
			if (Event::isGetEventW32API) {
				MSG msg;
				msg.hwnd = hwnd;
				msg.message = cmd;
				msg.wParam = wparam;
				msg.lParam = lparam;
				Event::m_globalMsg.push(msg);
			}

			/* Window Class
			 *
			 */
			Window* win = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

			switch (cmd) {
			case WM_CREATE:
			{
				/* Set user data to window
				 *
				 */
				SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lparam)->lpCreateParams);
				break;
			}

			case WM_CLOSE:
				win->m_event.push(Event(Event::Type::Closed));
				break;

			default:
				if (win == NULL) 
					return DefWindowProc(hwnd, cmd, wparam, lparam);
				else
					return win->GetEvent(cmd, wparam, lparam);
			}
		}


		//Register class
		struct initWndClass {

			initWndClass() {
				WNDCLASSW windowClass = { 0 };
				windowClass.lpfnWndProc = &Window::globalEvent;
				windowClass.hInstance = GetModuleHandleW(NULL);
				windowClass.lpszClassName = wndClassName;

				/* Testting
				 * If dont allow with OpenGL, We remove it
				 *
				 */
				windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
				windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
				windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);

				if (!RegisterClassW(&windowClass)) {
					std::cout << "Error register window class name!" << std::endl;
				}
				else {
					std::cout << "YUH register window class name!" << std::endl;
				}
			}

			~initWndClass() {
				UnregisterClassW(wndClassName, GetModuleHandleW(0));
				std::cout << "YUH unregister window class name!" << std::endl;
			}

		} __initWndClass__;


	}	//end window
}	//end yuh
