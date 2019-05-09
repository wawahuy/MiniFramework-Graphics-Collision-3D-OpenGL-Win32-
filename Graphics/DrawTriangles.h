#pragma once
#include "Drawing.h"

namespace yuh {
	namespace graphics {

		class GRAPHICS_API DrawTriangles : public Drawing
		{
		public:
			DrawTriangles(const Vec3f& p1, const Vec3f& p2, const Vec3f& p3);
			~DrawTriangles();
		};

	}
}

