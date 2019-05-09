#pragma once
#include "Export.h"
#include "Tranformable.h"
#include "Shader.h"
#include "Vertex.h"
#include <Math/Sphere.h>
#include <Math/AABB.h>
#include <string>


namespace yuh {
	namespace graphics {

		class GRAPHICS_API Renderable : public Tranformable
		{
			friend class Model;

		public:
			Renderable();
			~Renderable();

			/* Kết xuất đối tượng
			 * Program GPU (Shader) áp dụng chương trình bind cuối
			 * GLSL:
			 *			Model Matrix :   GLSL_YUH_MODEL
			 *
			 * Đa số không cần override vì sau khi áp dụng GPU Program sẽ gọi
			 *			this->drawWithOutShader();
			 *
			 */
			virtual void draw();


			/* Kết xuất đối tượng không GPU Program, không model matrix
			 * Cách áp dụng thủ công
			 * Cần override
			 *
			 */
			virtual void drawWithOutShader() = 0;


			/* Chỉ khi class derivide có hỗ trợ thì mới khả dụng
			 *
			 */
			bool   hasCoverSphere();

			Sphere getCoverSphere();

			bool   hasCoverAABB();

			AABB   getCoverAABB();

			virtual void   drawDebug();

		protected:
			void computeCoverAABB(const Vertex* v, size_t num);
			void computeCoverSphere(const Vertex* v, size_t num);

		private:
			bool	m_hasCoverSphere;
			bool	m_hasCoverAABB;
			Sphere	m_debugSphere;
			AABB	m_debugAABB;
			std::shared_ptr<Renderable> m_drawAABB;
			std::shared_ptr<Renderable> m_drawSphere;
		};


		typedef std::shared_ptr<Renderable> RenderablePtr;
	}
}