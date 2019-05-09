#pragma once
#include "Export.h"
#include "Shader.h"
#include <Math/Projection.h>

namespace yuh {
	namespace graphics {

		class GRAPHICS_API Camera
		{
		public:
			Camera();
			Camera(const Vec3f& position, const Vec3f& direction, const Vec3f& cameraUpWorld = Vec3f(0, 1, 0));
			~Camera();

			void setPosition(const Vec3f& position);
			void setDirection(const Vec3f& direction);
			void setUpWorld(const Vec3f& upWorld);
			void setPitch(float angle);
			void setYaw(float angle);

			math::Mat4f getMatrixView() const;
			Vec3f		getPosition();
			Vec3f		getDirection();
			Vec3f		getUpWorld();
			Vec3f		getUp();
			Vec3f		getRight();
			float		getPitch();
			float		getYaw();

			void pitch(float angle);
			void yaw(float angle);
			void translate(const Vec3f& trs);

		private:
			Vec3f		m_position;
			Vec3f		m_direction;
			Vec3f		m_upWorld;

			void		calcPitchYaw();
			void		calcDirectionWithPY();

			float		m_pitch;
			float		m_yaw;
			Vec3f		m_up;
			Vec3f		m_right;
		};

	}
}
