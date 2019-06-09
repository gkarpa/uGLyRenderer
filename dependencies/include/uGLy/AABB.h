#pragma once

#include <vector>
#include <algorithm>
#include "Vertex.h"

namespace uGLy
{
	class AABB
	{
	public:
		float xmin, xmax;
		float ymin, ymax;
		float zmin, zmax;

		AABB();

		void construct(std::vector<Vertex> & vertices);
	};
}