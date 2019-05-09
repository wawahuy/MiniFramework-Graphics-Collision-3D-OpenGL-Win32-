#pragma once
#include "Export.h"
#include "OpenGL.h"
#include <Windows.h>
#include <wingdi.h>
#include <iostream>
#include <System/NonCopyable.h>
#pragma comment(lib, "OpenGL32.lib")


namespace yuh {
	namespace window {

		std::string WINDOW_API GetLastErrorAsString();


		struct WINDOW_API ContextSetting {
			int cColorBits;
			int cDepthBits;
			int Samples;
		};


		class WINDOW_API WglContext : public NonCopyable
		{
		public:
			WglContext();
			WglContext(HWND hwnd, const ContextSetting &setting);
			~WglContext();

			void setGLWindow(HWND hwnd, const ContextSetting &setting);

			void setGLActive(bool active);

			bool getGLActive();

			void viewport(int x, int y, int width, int hegiht);

			void clearGL();

			void swapBufferGL();

			void closeGL();

			ContextSetting getContextSetting();


		private:
			HWND	m_hwnd;
			HDC		m_hdc;
			HGLRC	m_hrc;
			bool	m_active;

			ContextSetting m_setting;


			static WglContext* m_contextActive;

			/* Get best pixel format with setting
			 *
			 */
			int getBestPixelFormat();

			/* Create Surface render on Device
			 *
			 */
			bool createSurface();


			/* Create Context OpenGL
			 *
			 */
			bool createContextGL();


			/* Init glew lib
			 *
			 */
			void initGlew();

		};

	}	//end window
}	//end yuh

