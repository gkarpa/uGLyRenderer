#pragma once

#include "Camera.h"

namespace uGLy
{

	class ArcballCamera : public Camera
	{
	public:
		void calculateVectors();
		void processMousePosition(float xpos, float ypos);

		void activate(float xpos, float ypos);
		const glm::vec3 getArcballVector(float x, float y);
	};

}