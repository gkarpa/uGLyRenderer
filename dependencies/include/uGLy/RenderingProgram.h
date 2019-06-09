#pragma once

#include "glad.h"
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <unordered_map>


namespace uGLy
{

	class RenderingProgram
	{
	public:
		unsigned int id;
		std::vector<Shader> shaders;
		std::unordered_map<std::string, int> uniformLocationsMap;

		RenderingProgram();
		~RenderingProgram();

		void AttachShader(const Shader &shader);
		void Link();
		void Use();
		void Unuse();
		void FreeResources();
		void Delete();

		void SetUniformFloat(const std::string & uniformName, const float value);
		void SetUniformInt(const std::string & uniformName, const int value);
		void SetUniformVec3(const std::string & uniformName, const glm::vec3 & vec);
		void SetUniformVec4(const std::string & uniformName, const glm::vec4 & vec);
		void SetUniformMat3(const std::string & uniformName, const glm::mat3 & mat, const bool transpose = false);
		void SetUniformMat4(const std::string & uniformName, const glm::mat4 & mat, const bool transpose = false);

		int GetUniformLocation(const std::string & uniformName);
	};

}