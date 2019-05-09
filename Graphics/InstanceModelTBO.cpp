#include "InstanceModelTBO.h"


namespace yuh {
	namespace graphics {

		InstanceModelTBO::InstanceModelTBO()
		{
			initingTBO();
		}

		InstanceModelTBO::InstanceModelTBO(Model * model)
		{
			initingTBO();
			setWithModel(model);
		}


		InstanceModelTBO::~InstanceModelTBO()
		{
		}

		void InstanceModelTBO::bindTBO()
		{
			glBindBuffer(GL_TEXTURE_BUFFER, m_tbo);
		}

		void InstanceModelTBO::draw()
		{
			glActiveTexture(GL_TEXTURE4);
			glEnable(GL_TEXTURE_BUFFER);
			glBindTexture(GL_TEXTURE_BUFFER, m_tbo);
			
			/*Mat4f * matrices = (Mat4f *)glMapBuffer(GL_TEXTURE_BUFFER, GL_READ_WRITE);
			glUnmapBuffer(GL_TEXTURE_BUFFER);
			for (int i = 0; i < m_numModel; i++) std::cout << matrices[i] << std::endl;
*/
			for (int i = 0; i < m_numMesh; i++) {

				(*m_mesh)[i]->bind();

				for (int j = 0; j < (*m_mesh)[i]->m_numTexture; j++) {
					glActiveTexture(GL_TEXTURE0 + j);
					(*m_mesh)[i]->m_texture[j].bind();
				}

				glDrawElementsInstanced(GL_TRIANGLES, (*m_mesh)[i]->m_numIndices, GL_UNSIGNED_INT, 0, m_numModel);
			}

			glBindTexture(GL_TEXTURE_BUFFER, 0);
			glDisable(GL_TEXTURE_BUFFER);

		}

		void InstanceModelTBO::setWithModel(Model * model)
		{
			m_model = model;
			m_mesh = &model->m_meshs;
			m_numMesh = model->m_sizemesh;
		}

		void InstanceModelTBO::setWithMesh(std::vector<Mesh*>* meshs)
		{
			m_mesh = meshs;
			m_numMesh = meshs->size();
		}

		void InstanceModelTBO::setListTranform(Tranformable * tr, size_t num)
		{
			bindTBO();
			m_numModel = num;

			Mat4f *m = new Mat4f[num];
			for (int i = 0; i < num; i++) {
				m[i] = tr[i].getMat4();
				m[i].transpose();
			}
			glBufferData(GL_TEXTURE_BUFFER, sizeof(Mat4f)*num, m, GL_STATIC_DRAW);

			delete[] m;

			glBindTexture(GL_TEXTURE_BUFFER, 0);
		}

		void InstanceModelTBO::initingTBO()
		{
			glGenBuffers(1, &m_tbo);
			glBindBuffer(GL_TEXTURE_BUFFER, m_tbo);
			glTexBuffer(GL_TEXTURE_BUFFER, GL_RGBA32F, m_tbo);
			glBindBuffer(GL_TEXTURE_BUFFER, 0);
		}

	}
}