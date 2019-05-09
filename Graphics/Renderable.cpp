#include "Renderable.h"
#include "DrawBox.h"
#include <iostream>

namespace yuh {
	namespace graphics {

		Renderable::Renderable()
		{
		}


		Renderable::~Renderable()
		{
		}

		void Renderable::draw()
		{
			Shader::getShaderCurrent()->bind();
			Shader::getShaderCurrent()->uniformMat4f(GLSL_YUH_MODEL, getMat4());
			drawWithOutShader();
		}

		// DEBUG COVER
		bool Renderable::hasCoverAABB()
		{
			return m_hasCoverAABB;
		}

		AABB Renderable::getCoverAABB()
		{
			Mat4f mat = getMat4();
			Vec3f min = mat * m_debugAABB.getMin();
			Vec3f max = mat * m_debugAABB.getMax();
			return AABB(min, max);
		}

		void Renderable::computeCoverAABB(const Vertex* v, size_t num)
		{
			m_hasCoverAABB = true;

			// Get Position Array To Vertex Array
			std::vector<Vec3f> position;
			position.resize(num);
			for (int i = 0; i < num; i++) position[i] = v[i].position;
			
			// Compute min max
			m_debugAABB.computeWithVertices(&position[0], num);

			// Compute render
			Drawing* aabb = new DrawBox(m_debugAABB);
			aabb->setFill(false);
			aabb->setColor(Vec3f(1,0,0));
			m_drawAABB = RenderablePtr(aabb);
		}


		// Debug Sphere - Update
		bool Renderable::hasCoverSphere()
		{
			return m_hasCoverSphere;
		}


		Sphere Renderable::getCoverSphere()
		{
			Mat4f tranf = getMat4();
			Vec3f center = tranf * m_debugSphere.getCenter();
			float r = std::fmin(std::fmin(tranf.m_mtrix[0][0], tranf.m_mtrix[1][1]), tranf.m_mtrix[2][2]) * 0.5f * m_debugSphere.getR();
			return Sphere(center, r);
		}


		void Renderable::computeCoverSphere(const Vertex* v, size_t num)
		{
			m_hasCoverSphere = true;

			if (!m_hasCoverAABB) {
				computeCoverAABB(v, num);
			}
			
			Vec3f center = m_debugAABB.getMax()*0.5f + m_debugAABB.getMin()*0.5f;
			Vec3f size = m_debugAABB.getMax() - m_debugAABB.getMin();
			float R = std::fmax(std::fmax(size.x, size.y), size.z) / 2.0f;

			m_debugSphere.setCenter(center);
			m_debugSphere.setR(R);

			// Update draw sphere debug last
		}


		// Draw debug 
		void Renderable::drawDebug()
		{
			if (!m_hasCoverAABB && !m_hasCoverSphere) return;

			Shader::getShaderCurrent()->bind();
			Shader::getShaderCurrent()->uniformMat4f(GLSL_YUH_MODEL, getMat4());

			// debug AABB
			if (m_hasCoverAABB) {
				((Drawing*)m_drawAABB.get())->drawWithOutModel();
			}
		}
	}
}