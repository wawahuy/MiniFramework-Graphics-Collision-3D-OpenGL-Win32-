#include "GeometryFunction.h"

bool yuh::math::SameSide(Vec3f center, Vec3f v1, Vec3f v2)
{
	Vec3f cross1 = VectorCross(center, v1);
	Vec3f cross2 = VectorCross(center, v2);
	return cross1*cross2 >= 0;
}
