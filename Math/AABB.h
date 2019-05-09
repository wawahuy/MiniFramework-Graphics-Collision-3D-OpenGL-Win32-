#pragma once
#include "Vector3D.h"
#include <vector>

namespace yuh {
	namespace math {

		class AABB
		{
		public:
			AABB();
			AABB(const Vec3f& min, const Vec3f& max);
			~AABB();
			
			void set(const Vec3f& min, const Vec3f& max);

			void setWithOrigin(const Vec3f& origin, const Vec3f& halfsize);

			Vec3f getMax();

			Vec3f getMin();

			Vec3f getCenter();

			Vec3f getSize();

			/* Verices of AABB (8 vertex)
			 *			    v8 -------------- v5
			 *				  /|			/|
			 *				 / |		   / |
			 *			  v1---|--------v4-  | 
			 *				|v7	----------|--| v6
			 *			    | /			  | /
			 *				|/			  |/	
			 *			  v2-------------- v3
			 *
			 */

			Vec3f* getVertices();

			void translate(const Vec3f& trs);

			bool testOverlapAABB(const AABB& aabb);

			void computeWithVertices(const Vec3f* vertices, size_t num);

		private:
			bool  m_hasComputeVertex = false;
			Vec3f m_min;
			Vec3f m_max;
			Vec3f m_vertices[8];
		};


	}
}