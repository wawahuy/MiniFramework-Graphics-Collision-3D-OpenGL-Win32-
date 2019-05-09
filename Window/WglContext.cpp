#include "WglContext.h"
#include "wglew.h"
#include "Window.h"


namespace yuh {
	namespace window {

		/* Static object make current
		 *
		 */
		WglContext* WglContext::m_contextActive = NULL;

		bool Setup_Glew = false;

		/* Context
		 *
		 */
		WglContext::WglContext()
		{
		}

		WglContext::WglContext(HWND hwnd, const ContextSetting &setting)
		{
			setGLWindow(hwnd, setting);
		}

		WglContext::~WglContext()
		{
			closeGL();
		}

		void WglContext::setGLWindow(HWND hwnd, const ContextSetting &setting)
		{
			m_hwnd = hwnd;
			m_setting = setting;

			if (!createSurface()) {
				return;
			}

			if (!createContextGL()) {
				return;
			}

		}


		void WglContext::setGLActive(bool active)
		{
			if (m_active == active) return;

			if (active == false) {
				m_active = false;
				m_contextActive = NULL;
				wglMakeCurrent(m_hdc, NULL);
				return;
			}

			/* Disable active on current make
			 *
			 */
			if (m_contextActive != NULL) {
				m_contextActive->m_active = false;
			}

			/* Active Context
			 */
			wglMakeCurrent(m_hdc, m_hrc);

			m_active = true;

			m_contextActive = this;
		}

		bool WglContext::getGLActive()
		{
			return m_active;
		}

		void WglContext::viewport(int x, int y, int width, int hegiht)
		{
			glViewport(x, y, width, hegiht);
		}

		void WglContext::clearGL()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void WglContext::swapBufferGL()
		{
			SwapBuffers(m_hdc);
		}

		void WglContext::closeGL()
		{
			/*  If context current is active and close, it's null
			 *
			 */
			if (m_contextActive == this) {
				m_contextActive = NULL;
			}

			wglDeleteContext(m_hrc);
			ReleaseDC(m_hwnd, m_hdc);
		}

		ContextSetting WglContext::getContextSetting()
		{
			return m_setting;
		}

		bool WglContext::createSurface()
		{
			m_hdc = GetDC(m_hwnd);

			if (!m_hdc) {
				std::cout << "Error get Device Context! Error: " << GetLastErrorAsString().c_str() << std::endl;
				return false;
			}

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = m_setting.cColorBits;
			pfd.cDepthBits = m_setting.cDepthBits;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int bestFormat = getBestPixelFormat();

			if (!bestFormat) {
				bestFormat = ChoosePixelFormat(m_hdc, &pfd);
				if (!bestFormat) {
					std::cout << "Error choose format pixel in WglContext!" << std::endl;
					return false;
				}
			}

			if (!SetPixelFormat(m_hdc, bestFormat, &pfd)) {
				std::cout << "Error set format pixel in WglContext! (value: " << GetLastErrorAsString().c_str() << ")" << std::endl;
				return false;
			}

			return true;
		}

		bool WglContext::createContextGL()
		{
			m_hrc = wglCreateContext(m_hdc);

			if (!m_hrc)
			{
				return false;
			}
			
			//Make OpenGL Context Current
			setGLActive(true);

			//Init Glew
			if (!Setup_Glew) {
				initGlew();
				Setup_Glew = true;
			}

			return true;
		}



		void WglContext::initGlew()
		{
			if (glewInit() != GLEW_OK)
			{
				std::cerr << "GlewInit failed, aborting!" << std::endl;
			}
			else {
				std::cout << "GlewInit ok!" << std::endl;
			}
			Setup_Glew = true;
		}



		/* Get Best Pixel Format
		 * View on: http://www.3dcpptutorials.sk/index.php?id=5
		 *
		 */
		int WglContext::getBestPixelFormat()
		{
			HWND hWnd = CreateWindowW(wndClassName, L"", 0, 0, 0, 0, 0, 0, 0, 0, 0);
			if (hWnd == NULL) return 0;

			HDC hDC = GetDC(hWnd);
			if (hDC == NULL) return 0;

			PIXELFORMATDESCRIPTOR pfd;
			memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
			pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			pfd.nVersion = 1;
			pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			pfd.iPixelType = PFD_TYPE_RGBA;
			pfd.cColorBits = m_setting.cColorBits;
			pfd.cDepthBits = m_setting.cDepthBits;
			pfd.iLayerType = PFD_MAIN_PLANE;

			int PixelFormat = ChoosePixelFormat(hDC, &pfd);
			if (PixelFormat == 0) return 0;
			if (SetPixelFormat(hDC, PixelFormat, &pfd) == FALSE) return 0;

			HGLRC hGLRC = wglCreateContext(hDC);
			if (hGLRC == NULL) return 0;
			if (wglMakeCurrent(hDC, hGLRC) == FALSE) return 0;
			initGlew();

			int MSAAPixelFormat = 0;
			if (MSAAPixelFormat == 0 && m_setting.Samples > 0)
			{
				if (WGLEW_ARB_pixel_format && GLEW_ARB_multisample)
				{
					while (m_setting.Samples > 0)
					{
						UINT NumFormats = 0;

						int PFAttribs[] =
						{
							WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
							WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
							WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
							WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
							WGL_COLOR_BITS_ARB, m_setting.cColorBits,
							WGL_DEPTH_BITS_ARB, m_setting.cDepthBits,
							WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
							WGL_SAMPLE_BUFFERS_ARB, GL_TRUE,
							WGL_SAMPLES_ARB, m_setting.Samples,
							0
						};

						if (wglChoosePixelFormatARB(hDC, PFAttribs, NULL, 1, &MSAAPixelFormat, &NumFormats) == TRUE && NumFormats > 0) {
							std::cout << "----------------------------------" << std::endl;
							std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
							std::cout << "Best Samples: " << m_setting.Samples << std::endl;
							std::cout << "Best Format Pixel :" << MSAAPixelFormat << std::endl;
							std::cout << "Best Format Pixel Buffer: " << NumFormats << std::endl;
							std::cout << "TBO(texels): " << GL_MAX_TEXTURE_BUFFER_SIZE << std::endl;
							std::cout << "TBO(bytes): " << GL_MAX_TEXTURE_BUFFER_SIZE * sizeof(float) * 4 << std::endl;
							std::cout << "UBO: " << GL_MAX_UNIFORM_BLOCK_SIZE << std::endl;
							std::cout << "SSBO: " << GL_MAX_SHADER_STORAGE_BLOCK_SIZE << std::endl;
							std::cout << "----------------------------------" << std::endl;
							break;
						}

						m_setting.Samples--;
					}
				}
				else
				{
					m_setting.Samples = 0;
				}
			}

			wglDeleteContext(hGLRC);
			DestroyWindow(hWnd);

			return MSAAPixelFormat;
		}



		std::string GetLastErrorAsString()
		{
			//Get the error message, if any.
			DWORD errorMessageID = ::GetLastError();
			if (errorMessageID == 0)
				return std::string(); //No error message has been recorded

			LPSTR messageBuffer = nullptr;
			size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);

			std::string message(messageBuffer, size);

			//Free the buffer.
			LocalFree(messageBuffer);

			return message;
		}


	}
}