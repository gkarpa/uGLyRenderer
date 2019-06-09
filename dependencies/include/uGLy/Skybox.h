#pragma once

#include <vector>
#include <string>
#include "glad.h"
#include "Mesh.h"
#include "RenderingProgram.h"
#include "stb_image.h"
#include <glm/gtc/type_ptr.hpp>


namespace uGLy
{

	class Skybox
	{
	public:
		GLuint cubemapID, vao, vbo, ibo, samplerID;
		RenderingProgram renderingProgram;
		Skybox(const std::vector<std::string> &textures);
		Skybox(const std::string &rightSide, const std::string &leftSide,
			const std::string &topSide, const std::string &bottomSide,
			const std::string &backSide, const std::string &frontSide);
		~Skybox();

		void Draw(const glm::mat4 &viewProjection);

	private:
		void initialize(const std::vector<std::string> &textures);

		float vertices[108] = {
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
		};

		unsigned int indices[36] = {
			0, 6, 4,
			0, 2, 6,
			0, 3, 2,
			0, 1, 3,
			2, 7, 6,
			2, 3, 7,
			4, 6, 7,
			4, 7, 5,
			0, 4, 5,
			0, 5, 1,
			1, 5, 7,
			1, 7, 3
		};

		const char *vertexShaderSource = {
			"#version 460 core					\n"
			"layout(location = 0) in vec3 position;	\n"
			"out vec3 texCoords;	\n"
			"uniform mat4 viewProjection;	\n"
			"void main()	\n"
			"{	\n"
			"	texCoords = position;	\n"
			"	gl_Position = viewProjection * vec4(position, 1.0);	\n"
			"}"
		};

		const char *fragmentShaderSource = {
			"#version 460 core	\n"
			"out vec4 fragColor;	\n"
			"in vec3 texCoords;	\n"
			"layout (binding = 0) uniform samplerCube skybox;	\n"
			"void main()	\n"
			"{	\n"
			"	fragColor = texture(skybox, texCoords);	\n"
			"}"
		};
	};

}