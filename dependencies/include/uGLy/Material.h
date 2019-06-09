#pragma once

#include <string>
#include <vector>
#include <glm/vec3.hpp>
#include "Texture.h"

namespace uGLy
{

	class Material
	{
	public:
		Material();
		~Material();

		std::string name;

		glm::vec3 ambient, diffuse, specular, emissive, transparent;
		float opacity = 1.0f, shininess = 0.0f, shininessStrength = 1.0f;
		Texture *ambientMap = nullptr;
		Texture *diffuseMap = nullptr;
		Texture *specularMap = nullptr;
		Texture *normalMap = nullptr;

		bool HasAmbientMap();
		bool HasDiffuseMap();
		bool HasSpecularMap();
		bool HasNormalMap();
	};

}
