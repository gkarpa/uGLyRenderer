#pragma once

#include <glm/vec3.hpp>

namespace uGLy
{

	class Light
	{
	public:
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;

		void turnOn();
		void turnOff();

		Light(glm::vec3 ambient = glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3 diffuse = glm::vec3(1.0f, 1.0f, 1.0f),
			glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f),
			bool isOn = true);

	protected:
		bool isOn = true;
	};

}