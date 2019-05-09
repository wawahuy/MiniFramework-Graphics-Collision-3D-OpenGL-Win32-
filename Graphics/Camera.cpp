#include "Camera.h"


namespace yuh {
	namespace graphics {

		Camera::Camera()
		{
			m_upWorld = Vec3f(0, 1, 0);
		}

		Camera::Camera(const Vec3f & position, const Vec3f & direction, const Vec3f& cameraUp)
		{
			m_position = position;
			m_upWorld = cameraUp;
			m_direction = direction;
			calcPitchYaw();
		}

		Camera::~Camera()
		{
		}

		void Camera::setPosition(const Vec3f & position)
		{
			m_position = position;
		}

		void Camera::setDirection(const Vec3f & direction)
		{
			m_direction = direction;
			calcPitchYaw();
		}

		void Camera::setUpWorld(const Vec3f & up)
		{
			m_upWorld = up;
			calcDirectionWithPY();
		}

		void Camera::setPitch(float angle)
		{
			if (angle > 89.0f*3.14 / 180)
				m_pitch = 89.0f*3.14 / 180;
			if (angle < -89.0f*3.14 / 180)
				m_pitch = -89.0f*3.14 / 180;
			else
				m_pitch = angle;
			calcDirectionWithPY();
		}

		void Camera::setYaw(float angle)
		{
			m_yaw = angle;
			calcDirectionWithPY();
		}


		math::Mat4f Camera::getMatrixView() const
		{
			return math::LookAt(m_position, m_position + m_direction, m_upWorld);
		}

		Vec3f Camera::getPosition()
		{
			return m_position;
		}

		Vec3f Camera::getDirection()
		{
			return m_direction;
		}

		Vec3f Camera::getUpWorld()
		{
			return m_upWorld;
		}

		Vec3f Camera::getUp()
		{
			return m_up;
		}

		Vec3f Camera::getRight()
		{
			return m_right;
		}

		float Camera::getPitch()
		{
			return m_pitch;
		}

		float Camera::getYaw()
		{
			return m_yaw;
		}

		void Camera::pitch(float angle)
		{
			if (m_pitch + angle > 89.0f*3.14/180)
				m_pitch = 89.0f*3.14 / 180;
			if (m_pitch + angle < -89.0f*3.14 / 180)
				m_pitch = -89.0f*3.14 / 180;
			else
				m_pitch += angle;
			calcDirectionWithPY();
		}

		void Camera::yaw(float angle)
		{
			m_yaw += angle;
			calcDirectionWithPY();
		}


		void Camera::translate(const Vec3f & trs)
		{
			m_position = m_position + trs;
		}

		void Camera::calcPitchYaw()
		{
			m_pitch = asin(m_direction.y);
			m_yaw = atan2(m_direction.x, m_direction.z);
		}

		void Camera::calcDirectionWithPY()
		{
			m_direction.x = cos(m_yaw) * cos(m_pitch);
			m_direction.y = sin(m_pitch);
			m_direction.z = sin(m_yaw) * cos(m_pitch);
			m_direction = VectorNormalize(m_direction);
			m_right = VectorNormalize(VectorCross(m_direction, m_upWorld));  
			m_up = VectorNormalize(VectorCross(m_right, m_direction));
		}
	}
}