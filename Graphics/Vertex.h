#pragma once
#include "Export.h"
#include <Math/Vector2D.h>
#include <Math/Vector3D.h>
#include <Math/Vector4D.h>

namespace yuh {
	namespace graphics {

		const unsigned short MEM_POS_POS = 0;
		const unsigned short MEM_NORMAL_POS = sizeof(Vec3f);
		const unsigned short MEM_UV_POS = MEM_NORMAL_POS + sizeof(Vec3f);
		const unsigned short MEM_COLOR_POS = MEM_UV_POS + sizeof(Vec2f);

		struct Vertex {
			Vec3f position;
			Vec3f normal;
			Vec2f uv;
			Vec4f color;

			Vertex(Vec3f position, Vec3f normal, Vec2f uv, Vec4f color) :
				position(position),
				normal(normal),
				uv(uv),
				color(color) {
			}

			Vertex(Vec3f position, Vec3f normal, Vec2f uv) :
				position(position),
				normal(normal),
				uv(uv){
			}

			Vertex(Vec3f position, Vec3f normal) :
				position(position),
				normal(normal){
			}

			Vertex(Vec3f position, Vec2f textcoord) :
				position(position),
				normal(normal) {
			}

			Vertex(Vec3f position) :
				position(position) {
			}

			Vertex() {}
		};


		const unsigned short MEM_VERTEX = sizeof(Vertex);
	}
}