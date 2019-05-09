#pragma once
#include "Drawing.h"

namespace yuh {
	namespace graphics {

		class GRAPHICS_API DrawBox : public Drawing
		{
		public:
			DrawBox(const Vec3f& size);
			DrawBox(AABB aabb);
			~DrawBox();


		private:
			Vec3f m_size;

		};
	}
}

