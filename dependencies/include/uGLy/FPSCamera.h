#pragma once

#include "Camera.h"

namespace uGLy
{

	class FPSCamera : public Camera
	{
	public:
		void calculateVectors();
		void processMousePosition(float xpos, float ypos);
		void activate(float xpos, float ypos);
	};

}