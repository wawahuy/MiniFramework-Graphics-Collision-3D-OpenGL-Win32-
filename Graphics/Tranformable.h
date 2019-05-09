#pragma once
#include "Export.h"
#include <Math/Vector3D.h>
#include <Math/Mat4.h>
#include <Math/Affine.h>

namespace yuh {
	namespace graphics {

		using namespace math;

		/* Tranformable được sử dụng để thêm tọa độ cho đối tượng
		 * 
		 *
		 */
		class GRAPHICS_API Tranformable
		{
		public:
			friend class Renderable;

			Tranformable();
			~Tranformable();

			Tranformable& translate(const Vec3f& trans);
			Tranformable& scale(const Vec3f& scale);
			Tranformable& rotate(const Vec3f& rotate);

			Tranformable& setOrigin(const Vec3f& vec);
			Tranformable& setPosition(const Vec3f& vec);
			Tranformable& setScale(const Vec3f& vec);
			Tranformable& setRotate(const Vec3f& vec);

			Vec3f getOrigin();
			Vec3f getScale();
			Vec3f getRotate();
			Vec3f getPosition();

			Tranformable& update();

			Mat4f getMat4();

			const float* getPtr();
			
			operator const float*();

		protected:
			Vec3f m_origin;
			Vec3f m_rotate;
			Vec3f m_scale;
			Vec3f m_position;

		private:
			Mat4f m_tranform;
			bool  m_needUpdate;
		};

	}	//end graphics
}	//end yuh