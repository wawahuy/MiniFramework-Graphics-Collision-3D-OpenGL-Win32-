/*
	- Event.h
	- Project	:	Window Class
	- Author	:	Nguyen Gia Huy
	- Email		:	Kakahuy99@gmail.com
					Kakahuy104@gmail.com
	- Start		:	05/12/2018
	- Update	:
	- Deltail	:	Event in Window
*/

#pragma once
#include "Export.h"
#include <Windows.h>
#include <queue>
#include <Math/Vector2D.h>

#pragma region YUH KEY
#define YUH_KEY_Q 'Q'
#define YUH_KEY_W 'W'
#define YUH_KEY_E 'E'
#define YUH_KEY_R 'R'
#define YUH_KEY_T 'T'
#define YUH_KEY_Y 'Y'
#define YUH_KEY_U 'U'
#define YUH_KEY_I 'I'
#define YUH_KEY_O 'O'
#define YUH_KEY_P 'P'
#define YUH_KEY_A 'A'
#define YUH_KEY_S 'S'
#define YUH_KEY_D 'D'
#define YUH_KEY_F 'F'
#define YUH_KEY_G 'G'
#define YUH_KEY_H 'H'
#define YUH_KEY_J 'J'
#define YUH_KEY_K 'K'
#define YUH_KEY_L 'L'
#define YUH_KEY_Z 'Z'
#define YUH_KEY_X 'X'
#define YUH_KEY_C 'C'
#define YUH_KEY_V 'V'
#define YUH_KEY_B 'B'
#define YUH_KEY_N 'N'
#define YUH_KEY_M 'M'
#pragma endregion

namespace yuh {
	namespace window {
		
		
		/* Event Of Window
		 *
		 */
		class WINDOW_API Event
		{
		public:
			/* Type of event
			 *
			 */
			enum Type {
				Closed,
				Resize,
				MouseMove,
				KEY_PRESSED,
				KEY_RELEASE
			};

			
			/* Contruct
			 *
			 */
			Event() {}

			Event(Type type) { this->type = type; }
			

			/* Data type of event
			 *
			 */
			Type type;

			operator Type(){ return type; }


			/* Data of event
			 *
			 */
			Vec2i mouse;
			char  key;


			/* Global Event
			 * WIN32API
			 * 
			 */
			static bool pollEvent(MSG & msg);
			static bool isGetEventW32API;
			static std::queue<MSG> m_globalMsg;

		};

	}	//end window
}	//end yuh