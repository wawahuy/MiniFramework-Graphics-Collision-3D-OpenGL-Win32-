#pragma once
#include "Renderable.h"
#include "Mesh.h"

namespace yuh {
	namespace graphics {

		class GRAPHICS_API Model : public Renderable
		{
			friend class InstanceModelTBO;

		public:
			Model();
			~Model();
			void LoadFromFile(const std::string& str);

			// Overide abstract Renderable
			void drawWithOutShader();

			void free();

			std::vector<Mesh*>* getMeshs();

		private:
			std::vector<Mesh*> m_meshs;
			unsigned int	   m_sizemesh = 0;	
			string dir;
		};

	}
}

