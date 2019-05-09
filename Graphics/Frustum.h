#pragma once
#include "Export.h"
#include "Camera.h"
#include "DrawBox.h"
#include <Math/Plane.h>
#include <Math/AABB.h>
#include <Math/Mat4.h>

namespace yuh {
	namespace graphics {

		enum FRUSTUM_PLANE {
			FR_LEFT,
			FR_RIGHT,
			FR_FAR,
			FR_NEAR,
			FR_TOP,
			FR_BOTTOM,
			FR_SIZE
		};

		class GRAPHICS_API Frustum
		{
		public:
			Frustum();
			Frustum(const math::Mat4f& projection, const Camera& view);
			~Frustum();

			void set(const math::Mat4f& projection, const Camera& view);

			// test AABB in frustum
			bool testAABB(math::AABB& aabb);

			// draw debug
			void drawDebug();

		private:
			math::Mat4f m_projection;
			Camera		m_camera;
			math::Plane	m_plane[FRUSTUM_PLANE::FR_SIZE];

			void calcPlane();
		};

	}
}