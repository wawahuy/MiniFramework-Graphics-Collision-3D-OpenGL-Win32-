#pragma once
#include "Export.h"
#include "Model.h"
#include "Tranformable.h"

namespace yuh {
	namespace graphics {

		/* Ngưng hoạt động!!!
		 * Lỗi liên quan đến TBO, sớm sửa đổi
		 * Error day: 11/02/2019
		 *
		 */
		class GRAPHICS_API InstanceModelTBO
		{
		public:
			InstanceModelTBO();
			InstanceModelTBO(Model* model);
			~InstanceModelTBO();

			void bindTBO();

			void draw();

			void setWithModel(Model* model);

			void setWithMesh(std::vector<Mesh*> *meshs);

			void setListTranform(Tranformable* tr, size_t num);


		private:
			void	initingTBO();

			Model*	m_model;
			size_t  m_numModel = 0;
			GLuint  m_tbo;

			std::vector<Mesh*>	*m_mesh;
			size_t				 m_numMesh = 0;
		};

	}
}

