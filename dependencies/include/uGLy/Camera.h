#pragma once

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/quaternion_float.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace uGLy
{

	class Camera
	{
	private:
		glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 defaultPosition, defaultRight, defaultForward, defaultUp;

	public:
		int windowWidth, windowHeight;
		float pitch = 0.0f, yaw = 0.0f;
		float sensitivity = 0.5f;

		float lastX, lastY, currentX, currentY;
		bool active = false, firstMovement = true;

		glm::vec3 position;
		glm::vec3 right, forward, up; // forward is actually backwards (the z-axis)
		glm::mat4 viewMatrix;

		Camera();
		Camera(glm::vec3 & position, glm::vec3 & forward);
		Camera(glm::vec3 & position, glm::vec3 & forward, glm::vec3 & up, glm::vec3 & right);
		~Camera();

		const glm::mat4 & getViewMatrix();
		const glm::vec3 & getGlobalUp();

		void initialize(glm::vec3 & position);
		void initialize(glm::vec3 & position, glm::vec3 & forward);
		void initialize(glm::vec3 & position, glm::vec3 & forward, glm::vec3 & up, glm::vec3 & right);
		void setViewMatrix(const glm::mat4& matrix);
		void refreshViewMatrix();
		void reset();

		virtual void calculateVectors() = 0;
		virtual void processMousePosition(float xpos, float ypos) = 0;
		virtual void activate(float xpos, float ypos) = 0;

		void deactivate();
	};

}