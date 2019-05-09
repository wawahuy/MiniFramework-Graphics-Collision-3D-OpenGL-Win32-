#include "Frustum.h"


namespace yuh {
	namespace graphics {

		Frustum::Frustum()
		{
		}

		Frustum::Frustum(const math::Mat4f & projection, const Camera& camera)
		{
			set(projection, camera);
		}


		Frustum::~Frustum()
		{
		}

		void Frustum::set(const math::Mat4f & projection, const Camera& camera)
		{
			m_projection = projection;
			m_camera = camera;
			calcPlane();
		}

		bool Frustum::testAABB(math::AABB & aabb)
		{
			Vec3f * vertexAABB = aabb.getVertices();

			for (int i = 0; i < 6; i++) {
				if (m_plane[i] * vertexAABB[0] >= 0) continue;
				if (m_plane[i] * vertexAABB[1] >= 0) continue;
				if (m_plane[i] * vertexAABB[2] >= 0) continue;
				if (m_plane[i] * vertexAABB[3] >= 0) continue;
				if (m_plane[i] * vertexAABB[4] >= 0) continue;
				if (m_plane[i] * vertexAABB[5] >= 0) continue;
				if (m_plane[i] * vertexAABB[6] >= 0) continue;
				if (m_plane[i] * vertexAABB[7] >= 0) continue;

				return false;
			}
			return true;
		}

		void Frustum::drawDebug()
		{
			DrawBox dCam(Vec3f(5, 5, 5));
			dCam.setPosition(m_camera.getPosition());
			dCam.draw();
		}

		void Frustum::calcPlane()
		{
			// Plane compute of Author Hartmann/Gribbs: http://www8.cs.umu.se/kurser/5DV051/HT12/lab/plane_extraction.pdf
			float a, b, c, d;
			Mat4f comboMatrix = m_projection*m_camera.getMatrixView();

			// Left clipping plane
			a = comboMatrix._41 + comboMatrix._11;
			b = comboMatrix._42 + comboMatrix._12;
			c = comboMatrix._43 + comboMatrix._13;
			d = comboMatrix._44 + comboMatrix._14;
			m_plane[FR_LEFT].set(a, b, c ,d);

			// Right clipping plane
			a = comboMatrix._41 - comboMatrix._11;
			b = comboMatrix._42 - comboMatrix._12;
			c = comboMatrix._43 - comboMatrix._13;
			d = comboMatrix._44 - comboMatrix._14;
			m_plane[FR_RIGHT].set(a, b, c, d);

			// Top clipping plane
			a = comboMatrix._41 - comboMatrix._21;
			b = comboMatrix._42 - comboMatrix._22;
			c = comboMatrix._43 - comboMatrix._23;
			d = comboMatrix._44 - comboMatrix._24;
			m_plane[FR_TOP].set(a, b, c, d);

			// Bottom clipping plane
			a = comboMatrix._41 + comboMatrix._21;
			b = comboMatrix._42 + comboMatrix._22;
			c = comboMatrix._43 + comboMatrix._23;
			d = comboMatrix._44 + comboMatrix._24;
			m_plane[FR_BOTTOM].set(a, b, c, d);

			// Near clipping plane
			a = comboMatrix._41 + comboMatrix._31;
			b = comboMatrix._42 + comboMatrix._32;
			c = comboMatrix._43 + comboMatrix._33;
			d = comboMatrix._44 + comboMatrix._34;
			m_plane[FR_NEAR].set(a, b, c, d);

			// Far clipping plane
			a = comboMatrix._41 - comboMatrix._31;
			b = comboMatrix._42 - comboMatrix._32;
			c = comboMatrix._43 - comboMatrix._33;
			d = comboMatrix._44 - comboMatrix._34;
			m_plane[FR_FAR].set(a, b, c, d);

			//for (int i = 0; i < FR_SIZE; i++) m_plane[i].normalize();
		}

	}
}