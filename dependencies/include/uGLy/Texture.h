#pragma once

#include <string>
#include <algorithm>
#include <cmath>
#include "glad.h"


namespace uGLy
{

	class Texture {
	public:
		std::string fullPathName;
		GLuint id = 0, samplerId;

		int xDimension, yDimension;
		int numChannels;
		Texture();
		~Texture();
	};

}
