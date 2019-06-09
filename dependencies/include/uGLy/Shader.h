#pragma once

#include "glad.h"
#include <iostream>
#include <string>
#include <fstream>


namespace uGLy
{

	class Shader {
	public:
		GLuint id;

		Shader();
		~Shader();
		bool CreateShaderFromFile(GLenum shaderType, const char *shaderPath);
		bool CreateShaderFromSource(GLenum shaderType, const char *shaderSource);
	};

}