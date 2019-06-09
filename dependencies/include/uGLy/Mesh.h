#pragma once

//#include <glm/vec3.hpp>
#include <vector>
#include <glm/mat4x4.hpp>
#include "RenderingProgram.h"
#include "glad.h"
#include "Vertex.h"
#include "Material.h"
#include "AABB.h"


namespace uGLy
{

	class Mesh
	{
	public:
		unsigned int vao, vbo, ibo;
		glm::mat4 transformationMatrix;
		RenderingProgram renderingProgram;
		Material material;
		AABB aabb;

		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;

		Mesh();
		~Mesh();
		void Draw();
		void calculateAABB();
	};

}
