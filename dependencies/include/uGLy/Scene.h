#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include "Camera.h"
#include "Mesh.h"
#include "TextureManager.h"
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/common.hpp>
#include <cstddef>
#include "Skybox.h"
#include "PointLight.h"


namespace uGLy
{

	class Scene {
	public:
		int windowWidth;
		int windowHeight;

		Camera *camera;
		TextureManager textureManager;
		std::vector<Mesh*> meshes;
		float zNear, zFar, fovy, defaultFovy;
		glm::mat4 projectionMatrix;
		Skybox *skybox;
		PointLight pointLight;

		Scene(int width = 1280, int height = 720, float fovy = 60.0f, float zNear = 0.1f, float zFar = 1000.0f);
		~Scene();

		void addCamera(Camera *cam);
		const glm::mat4& getProjectionMatrix();
		void updateProjectionMatrix();
		void updateFovY(float fovy);
		void render(double currentTime);
		void resize(int newWidth, int newHeight);
		void reset();
		void clear();
	};

}