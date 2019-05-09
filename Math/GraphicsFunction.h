#pragma once
#include "Vector3D.h"

namespace yuh {
	namespace math {

		void CalcTrianglesNormal2(Vec3f *vertices, Vec3f *&outNormals, unsigned int num);

		void CalcRectanglesNormal2(Vec3f *vertices, Vec3f *&outNormals, unsigned int num);

	}
}