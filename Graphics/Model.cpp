#include "Model.h"
#include "Texture.h"
#include <Math/Mat4.h>
#include <Graphics/assimp/Importer.hpp>
#include <Graphics/assimp/postprocess.h>
#include <Graphics/assimp/scene.h>
#pragma comment(lib, "assimp-vc140-mt.lib")

namespace yuh {
	namespace graphics {

		Model::Model()
		{
		}

		Model::~Model()
		{
		}


		/* Assimp Function
		 *
		 */
		std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName, string dir)
		{
			vector<Texture> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);

				Texture texture;
				texture.set((dir+str.C_Str()).c_str());
				texture.TypeName = typeName;
				textures.push_back(texture);

				//std::cout << (dir + str.C_Str()).c_str() << std::endl;
			}
			return textures;
		}


		Mesh* AssimpProcessMesh(aiMesh *mesh, const aiScene *scene, const aiMatrix4x4& trans, std::string dir) {
			std::vector<Vertex> vertices;
			std::vector<uint> indices;
			std::vector<Texture> textures;

			//Copy tranform
			math::Mat4f transform = *(Mat4f*)&trans.a1;
			

			// std::cout << "mesh->mNumVertices: " << mesh->mNumVertices << std::endl;
			for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
			{
				Vertex vertex;
				// process vertex positions, normals and texture coordinates
				vertex.position.x = mesh->mVertices[i].x;
				vertex.position.y = mesh->mVertices[i].y;
				vertex.position.z = mesh->mVertices[i].z;

				// UVs coordinates
				if (mesh->mTextureCoords[0]) // domes the mesh contain texture coordinates?
				{
					vertex.uv.x = mesh->mTextureCoords[0][i].x;
					vertex.uv.y = mesh->mTextureCoords[0][i].y;
				}
				else {
					vertex.uv.x = 0.0f;
					vertex.uv.y = 0.0f;
				}

				// Normals
				if (mesh->mNormals != NULL) {
					vertex.normal.x = mesh->mNormals[i].x;
					vertex.normal.y = mesh->mNormals[i].y;
					vertex.normal.z = mesh->mNormals[i].z;
				}

				//Tangent


				//Bitangent



				// Update with tranform
				// --------------------
				vertex.position = (transform*Vec4f(vertex.position, 1.0)).xyz;
				vertex.normal = VectorNormalize((transform*Vec4f(vertex.normal, 0.0)).xyz);

				//
				// TODO: Handle tangent and bittangent
				//
				vertices.push_back(vertex);
			}


			// process indices
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++) {
					indices.push_back(face.mIndices[j]);
				}
			}

			// process material (textures)
			if (mesh->mMaterialIndex >= 0)
			{
				// Handle materials
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				
				// 1. diffuse maps
				vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", dir);
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				// 2. specular maps
				vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", dir);
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
				
				// 3. normal maps
				std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", dir);
				textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
				
				// 4. height maps
				std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", dir);
				textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
			}



			Mesh *n_mesh = new Mesh(&vertices[0], vertices.size(), &indices[0], indices.size());
			n_mesh->setTextures(textures);

			return n_mesh;
		}



		void AssimpProcessNode(aiNode *node, const aiScene *scene, std::vector<Mesh*> &m_meshs, std::string dir) {
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				aiMatrix4x4 trans = node->mTransformation;
				m_meshs.push_back(AssimpProcessMesh(mesh, scene, trans, dir));
			}
			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				AssimpProcessNode(node->mChildren[i], scene, m_meshs, dir);
			}
		}


		

		/* Use assimp
		 * 
		 */
		void Model::LoadFromFile(const std::string & filename)
		{
			Assimp::Importer importer;

			const aiScene* scene = importer.ReadFile(
				filename,
				aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

			// Check if there was errors with 
			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cout << importer.GetErrorString() << std::endl;
				return;
			}

			// Dir path
			int pos = filename.find_last_of('/');
			if (pos > 0)
				dir = filename.substr(0, pos + 1);
			else
				dir = "";

			AssimpProcessNode(scene->mRootNode, scene, m_meshs, dir);

			m_sizemesh = m_meshs.size();

			// comment
			size_t numIndices = 0;
			for (int i = 0; i < m_sizemesh; i++) numIndices += m_meshs[i]->getNumIndices();
			std::cout << "------------------------------------------------" << std::endl;
			std::cout << "Assimp Loading: " << filename.c_str() << std::endl;
			std::cout << "Assimp Indices: " << numIndices << std::endl;
			std::cout << "------------------------------------------------" << std::endl;

			// calc cover AABB
			std::vector<Vertex> vertices;
			vertices.resize(2 * m_sizemesh);
			for (int i = 0; i < m_sizemesh; i++) {
				AABB aabb = m_meshs[i]->m_debugAABB;
				vertices[i*2] = Vertex(aabb.getMin());
				vertices[i*2+1] = Vertex(aabb.getMax());
			}
			computeCoverAABB(&vertices[0], vertices.size());
			computeCoverSphere(&vertices[0], vertices.size());

		}

		/*void Model::draw()
		{
			Renderable::draw();
			for (int i = 0; i < m_sizemesh; i++) {
				m_meshs[i]->drawWithOutShader();
			}
		}*/

		void Model::drawWithOutShader()
		{
			for (int i = 0; i < m_sizemesh; i++) {
				m_meshs[i]->drawWithOutShader();
			}
		}

		void Model::free()
		{
			for (int i = m_sizemesh-1; i > -1; i--) {
				m_meshs[i]->free();
				delete m_meshs[i];
			}
			m_meshs.clear();
		}

		std::vector<Mesh*>* Model::getMeshs()
		{
			return &m_meshs;
		}


	}
}
