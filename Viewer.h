#pragma once

#include "uGLy/Scene.h"
#include "uGLy/Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <cstddef>

class Viewer
{
public:
	Viewer();
	~Viewer();

	uGLy::Scene *scene;
	std::vector<uGLy::Mesh*> import(const std::string & path);
	void render(double currentTime);
};
