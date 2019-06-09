#pragma once

#include "Light.h"

namespace uGLy
{

	class DirectionalLight : public Light
	{
	public:
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);

		DirectionalLight(glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f));

	};

}