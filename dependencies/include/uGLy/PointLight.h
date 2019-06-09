#pragma once

#include "Light.h"
#include "Mesh.h"

namespace uGLy
{

	class PointLight : public Light
	{
	public:
		glm::vec3 position;
		float kconstant;
		float klinear;
		float kquadratic;
		Mesh *mesh;

		PointLight(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
			float kconstant = 1.0f,
			float klinear = 0.0f,
			float kquadratic = 0.0f);
	};

}
