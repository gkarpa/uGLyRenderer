#include "Viewer.h"

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

std::vector<uGLy::Mesh*> Viewer::import(const std::string & path)
{
	Assimp::Importer importer;
	std::vector<uGLy::Mesh*> importedMeshes;

	std::cout << "Reading file " << path << " ..." << std::endl;
	const aiScene *sc = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (!sc) {
		std::cout << "Error parsing the file!" << std::endl;
		std::cout << importer.GetErrorString() << std::endl;
	}
	else
	{
		std::cout << "Processing file " << path << " ..." << std::endl;
		for (unsigned int i = 0; i < sc->mNumMeshes; i++)
		{
			uGLy::Mesh *mesh = new uGLy::Mesh();

			for (unsigned int j = 0; j < sc->mMeshes[i]->mNumVertices; j++)
			{
				uGLy::Vertex vertex;
				vertex.position.x = sc->mMeshes[i]->mVertices[j].x;
				vertex.position.y = sc->mMeshes[i]->mVertices[j].y;
				vertex.position.z = sc->mMeshes[i]->mVertices[j].z;

				if (sc->mMeshes[i]->HasNormals())
				{
					vertex.normal.x = sc->mMeshes[i]->mNormals[j].x;
					vertex.normal.y = sc->mMeshes[i]->mNormals[j].y;
					vertex.normal.z = sc->mMeshes[i]->mNormals[j].z;

					if (sc->mMeshes[i]->HasTangentsAndBitangents())
					{
						vertex.tangent.x = sc->mMeshes[i]->mTangents[j].x;
						vertex.tangent.y = sc->mMeshes[i]->mTangents[j].y;
						vertex.tangent.z = sc->mMeshes[i]->mTangents[j].z;

						vertex.bitangent.x = sc->mMeshes[i]->mBitangents[j].x;
						vertex.bitangent.y = sc->mMeshes[i]->mBitangents[j].y;
						vertex.bitangent.z = sc->mMeshes[i]->mBitangents[j].z;

					}
				}

				if (sc->mMeshes[i]->HasVertexColors(0))
				{
					vertex.color.r = sc->mMeshes[i]->mColors[0][j].r / 255.0f;
					vertex.color.g = sc->mMeshes[i]->mColors[0][j].g / 255.0f;
					vertex.color.b = sc->mMeshes[i]->mColors[0][j].b / 255.0f;
					vertex.color.a = sc->mMeshes[i]->mColors[0][j].a;
				}
				else
				{
					vertex.color.r = 1.0f;
					vertex.color.g = 1.0f;
					vertex.color.b = 1.0f;
					vertex.color.a = 1.0f;
				}

				if (sc->mMeshes[i]->HasTextureCoords(0))
				{
					vertex.texCoord.s = sc->mMeshes[i]->mTextureCoords[0][j].x;
					vertex.texCoord.t = sc->mMeshes[i]->mTextureCoords[0][j].y;
					//vertex.texCoord.p = sc->mMeshes[i]->mTextureCoords[0][j].z;
				}

				mesh->vertices.push_back(vertex);
			}

			if (sc->mMeshes[i]->HasFaces())
			{
				for (unsigned int j = 0; j < sc->mMeshes[i]->mNumFaces; j++)
				{
					for (unsigned int k = 0; k < sc->mMeshes[i]->mFaces[j].mNumIndices; k++)
					{
						mesh->indices.push_back(sc->mMeshes[i]->mFaces[j].mIndices[k]);
					}
				}
			}

			if (sc->HasMaterials())
			{
				aiMaterial *mat = sc->mMaterials[sc->mMeshes[i]->mMaterialIndex];
				aiString stringProperty;
				aiColor3D colorProperty;
				float floatProperty;

				if (mat->Get(AI_MATKEY_NAME, stringProperty) == AI_SUCCESS)
				{
					mesh->material.name = stringProperty.C_Str();
				}
				if (mat->Get(AI_MATKEY_COLOR_AMBIENT, colorProperty) == AI_SUCCESS)
				{
					mesh->material.ambient = glm::vec3(colorProperty.r, colorProperty.g, colorProperty.b);
				}
				if (mat->Get(AI_MATKEY_COLOR_DIFFUSE, colorProperty) == AI_SUCCESS)
				{
					mesh->material.diffuse = glm::vec3(colorProperty.r, colorProperty.g, colorProperty.b);
				}
				if (mat->Get(AI_MATKEY_COLOR_SPECULAR, colorProperty) == AI_SUCCESS)
				{
					mesh->material.specular = glm::vec3(colorProperty.r, colorProperty.g, colorProperty.b);
				}
				if (mat->Get(AI_MATKEY_COLOR_EMISSIVE, colorProperty) == AI_SUCCESS)
				{
					mesh->material.emissive = glm::vec3(colorProperty.r, colorProperty.g, colorProperty.b);
				}
				if (mat->Get(AI_MATKEY_COLOR_TRANSPARENT, colorProperty) == AI_SUCCESS)
				{
					mesh->material.transparent = glm::vec3(colorProperty.r, colorProperty.g, colorProperty.b);
				}
				if (mat->Get(AI_MATKEY_OPACITY, floatProperty) == AI_SUCCESS)
				{
					mesh->material.opacity = floatProperty;
				}
				if (mat->Get(AI_MATKEY_SHININESS, floatProperty) == AI_SUCCESS)
				{
					mesh->material.shininess = floatProperty;
				}
				if (mat->Get(AI_MATKEY_SHININESS_STRENGTH, floatProperty) == AI_SUCCESS)
				{
					mesh->material.shininessStrength = floatProperty;
				}
				if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_AMBIENT, 0), stringProperty) == AI_SUCCESS)
				{
					std::size_t lastSlashPos = path.find_last_of("/\\");
					uGLy::Texture *tex = scene->textureManager.CreateTextureFromFile(path.substr(0, lastSlashPos) + "\\" + std::string(stringProperty.C_Str()));
					if (tex)
					{
						mesh->material.ambientMap = tex;
					}
				}
				if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_DIFFUSE, 0), stringProperty) == AI_SUCCESS)
				{
					std::size_t lastSlashPos = path.find_last_of("/\\");
					uGLy::Texture *tex = scene->textureManager.CreateTextureFromFile(path.substr(0, lastSlashPos) + "\\" + std::string(stringProperty.C_Str()));
					if (tex)
					{
						mesh->material.diffuseMap = tex;
					}
				}
				if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_SPECULAR, 0), stringProperty) == AI_SUCCESS)
				{
					std::size_t lastSlashPos = path.find_last_of("/\\");
					uGLy::Texture *tex = scene->textureManager.CreateTextureFromFile(path.substr(0, lastSlashPos) + "\\" + std::string(stringProperty.C_Str()));
					if (tex)
					{
						mesh->material.specularMap = tex;
					}
				}
				if (mat->Get(AI_MATKEY_TEXTURE(aiTextureType_NORMALS, 0), stringProperty) == AI_SUCCESS)
				{
					std::size_t lastSlashPos = path.find_last_of("/\\");
					uGLy::Texture *tex = scene->textureManager.CreateTextureFromFile(path.substr(0, lastSlashPos) + "\\" + std::string(stringProperty.C_Str()));
					if (tex)
					{
						mesh->material.normalMap = tex;
					}
				}
				//if (mat->Get)
				//std::cout << mat->GetTextureCount(aiTextureType_DIFFUSE) << std::endl;
			}

			glCreateVertexArrays(1, &mesh->vao);
			glBindVertexArray(mesh->vao);

			glCreateBuffers(1, &mesh->vbo);
			glNamedBufferStorage(mesh->vbo, sizeof(uGLy::Vertex) * mesh->vertices.size(), mesh->vertices.data(), 0);
			glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);

			glVertexArrayVertexBuffer(mesh->vao, 0, mesh->vbo, 0, sizeof(uGLy::Vertex));

			glEnableVertexArrayAttrib(mesh->vao, 0);
			glVertexArrayAttribFormat(mesh->vao, 0, 3, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, position));
			glVertexArrayAttribBinding(mesh->vao, 0, 0);

			glEnableVertexArrayAttrib(mesh->vao, 1);
			glVertexArrayAttribFormat(mesh->vao, 1, 4, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, color));
			glVertexArrayAttribBinding(mesh->vao, 1, 0);

			glEnableVertexArrayAttrib(mesh->vao, 2);
			glVertexArrayAttribFormat(mesh->vao, 2, 3, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, normal));
			glVertexArrayAttribBinding(mesh->vao, 2, 0);

			glEnableVertexArrayAttrib(mesh->vao, 3);
			glVertexArrayAttribFormat(mesh->vao, 3, 2, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, texCoord));
			glVertexArrayAttribBinding(mesh->vao, 3, 0);

			glEnableVertexArrayAttrib(mesh->vao, 4);
			glVertexArrayAttribFormat(mesh->vao, 4, 3, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, tangent));
			glVertexArrayAttribBinding(mesh->vao, 4, 0);
			
			glEnableVertexArrayAttrib(mesh->vao, 5);
			glVertexArrayAttribFormat(mesh->vao, 5, 3, GL_FLOAT, GL_FALSE, offsetof(uGLy::Vertex, bitangent));
			glVertexArrayAttribBinding(mesh->vao, 5, 0);

			glCreateBuffers(1, &mesh->ibo);
			glNamedBufferStorage(mesh->ibo, sizeof(unsigned int) * sc->mMeshes[i]->mNumFaces * 3, mesh->indices.data(), 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);

			glVertexArrayElementBuffer(mesh->vao, mesh->ibo);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			mesh->calculateAABB();
			importedMeshes.push_back(mesh);
		}
	}
	std::cout << "File " << path << " import finished." << std::endl;
	return importedMeshes;
}

void Viewer::render(double currentTime)
{
	glm::mat4 mvp, viewProjection;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 view = scene->camera->getViewMatrix();
	glm::mat4 projection = scene->getProjectionMatrix();

	scene->pointLight.mesh->transformationMatrix = glm::translate(glm::mat4(1.0f), scene->pointLight.position) * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f, 0.1f, 0.1f));
	if (scene->skybox)
	{
		viewProjection = projection * glm::mat4(glm::mat3(view));
		scene->skybox->Draw(viewProjection);
	}

	for (auto mesh : scene->meshes) {
		if (mesh->vao) {
			glm::mat4 model = mesh->transformationMatrix;
			mvp = projection * view * model;
			auto program = mesh->renderingProgram;
			program.Use();

			program.SetUniformMat4("model", model);
			program.SetUniformMat4("modelViewProjection", mvp);
			program.SetUniformMat4("modelView", view * model);
			program.SetUniformMat4("view", view);
			program.SetUniformMat3("normalMatrix", glm::transpose(glm::inverse(glm::mat3(view * model))));
			program.SetUniformInt("hasAmbientMap", mesh->material.HasAmbientMap());
			program.SetUniformInt("hasDiffuseMap", mesh->material.HasDiffuseMap());
			program.SetUniformInt("hasSpecularMap", mesh->material.HasSpecularMap());
			program.SetUniformInt("hasNormalMap", mesh->material.HasNormalMap());
			program.SetUniformVec3("material.ambient", mesh->material.ambient);
			program.SetUniformVec3("material.diffuse", mesh->material.diffuse);
			program.SetUniformVec3("material.specular", mesh->material.specular);
			program.SetUniformVec3("material.emissive", mesh->material.emissive);
			program.SetUniformVec3("material.transparent", mesh->material.transparent);
			program.SetUniformFloat("material.opacity", mesh->material.opacity);
			program.SetUniformFloat("material.shininess", mesh->material.shininess);
			program.SetUniformFloat("material.shininessStrength", mesh->material.shininessStrength);
			program.SetUniformVec3("light.position", scene->pointLight.position);
			program.SetUniformVec3("light.ambient", scene->pointLight.ambient);
			program.SetUniformVec3("light.diffuse", scene->pointLight.diffuse);
			program.SetUniformVec3("light.specular", scene->pointLight.specular);
			program.SetUniformFloat("light.kconstant", scene->pointLight.kconstant);
			program.SetUniformFloat("light.klinear", scene->pointLight.klinear);
			program.SetUniformFloat("light.kquadratic", scene->pointLight.kquadratic);

			mesh->Draw();
			program.Unuse();
		}
	}
}
