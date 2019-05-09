#include "GraphicsFunction.h"
#include <map>

void yuh::math::CalcTrianglesNormal2(Vec3f * vertices, Vec3f *& outNormals, unsigned int num)
{
	for (int i = 0; i < num; i+=3) {
		Vec3f v1 = vertices[i + 1] - vertices[i];
		Vec3f v2 = vertices[i + 2] - vertices[i];
		Vec3f normal = VectorNormalize(VectorCross(v1, v2));

		outNormals[i] = normal;
		outNormals[i+1] = normal;
		outNormals[i+2] = normal;
	}


	std::map<std::string, Vec3f> totalNormal;
	for (int i = 0; i < num; i++) {
		std::string strVec = VectorToString(vertices[i]);
		
		if (totalNormal.find(strVec) == totalNormal.end()) {
			totalNormal.insert(std::pair<std::string, Vec3f>(strVec, outNormals[i]));
		}
		else {
			totalNormal[strVec] = totalNormal[strVec] + outNormals[i];
		}
	}


	for (int i = 0; i < num; i++) {
		outNormals[i] = VectorNormalize(totalNormal[VectorToString(vertices[i])]);
	}
}

void yuh::math::CalcRectanglesNormal2(Vec3f * vertices, Vec3f *& outNormals, unsigned int num)
{
	for (int i = 0; i < num; i += 4) {
		Vec3f v1 = vertices[i + 1] - vertices[i];
		Vec3f v2 = vertices[i + 3] - vertices[i];
		Vec3f normal = VectorNormalize(VectorCross(v1, v2));

		outNormals[i] = normal;
		outNormals[i + 1] = normal;
		outNormals[i + 2] = normal;
		outNormals[i + 3] = normal;
	}


	//std::map<std::string, Vec3f> totalNormal;
	//for (int i = 0; i < num; i++) {
	//	std::string strVec = VectorToString(vertices[i]);

	//	if (totalNormal.find(strVec) == totalNormal.end()) {
	//		totalNormal.insert(std::pair<std::string, Vec3f>(strVec, outNormals[i]));
	//	}
	//	else {
	//		totalNormal[strVec] = totalNormal[strVec] + outNormals[i];
	//	}
	//}


	//for (int i = 0; i < num; i++) {
	//	outNormals[i] = VectorNormalize(totalNormal[VectorToString(vertices[i])]);
	//}
}
