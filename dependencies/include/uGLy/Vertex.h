#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>


namespace uGLy
{

	struct Vertex
	{
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;
		glm::vec2 texCoord;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

}