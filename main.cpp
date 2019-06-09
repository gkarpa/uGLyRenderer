#include <iostream>

#define GLFW_INCLUDE_NONE

#include "uGLy/glad.h"
#include "uGLy/Scene.h"
#include "uGLy/ArcballCamera.h"
#include "Viewer.h"
#include <GLFW/glfw3.h>

uGLy::Scene *scene;
Viewer *viewer;

float cameraSpeed;

void APIENTRY openglErrorCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	std::cout << "OpenGL Error:" << message << std::endl;
}

void errorCallback (int error, const char *description)
{
	std::cout << description << std::endl;
}

void keyCallback (GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_REPEAT)
	{
		if (key == GLFW_KEY_S)
		{
			scene->camera->position += scene->camera->forward * cameraSpeed;
			scene->camera->refreshViewMatrix();
		}
		else if (key == GLFW_KEY_W)
		{
			scene->camera->position -= scene->camera->forward * cameraSpeed;
			scene->camera->refreshViewMatrix();
		}
	}
	else if (action == GLFW_PRESS)
	{
		if (key == GLFW_KEY_ESCAPE)
		{
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		else if (key == GLFW_KEY_R)
		{
			scene->reset();			
		}
		else if (key == GLFW_KEY_Q)
		{
			scene->clear();
		}
		else if (key == GLFW_KEY_S) {
			scene->camera->position += scene->camera->forward * cameraSpeed;			
			scene->camera->refreshViewMatrix();
		}
		else if (key == GLFW_KEY_W) {
			scene->camera->position -= scene->camera->forward * cameraSpeed;
			scene->camera->refreshViewMatrix();
		}
		
		else if (key == GLFW_KEY_F) {
			int polygonMode[2];
			glGetIntegerv(GL_POLYGON_MODE, polygonMode);
			if (polygonMode[0] == GL_LINE) {
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
		}
		else if (key == GLFW_KEY_C) {
			if (glIsEnabled(GL_CULL_FACE)) {
				glDisable(GL_CULL_FACE);
			}
			else {
				glEnable(GL_CULL_FACE);
			}
		}
	}
}


void cursorPositionCallback(GLFWwindow *window, double xpos, double ypos)
{
	if (scene->camera->active)
	{
		scene->camera->processMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
	}	
}

void mouseButtonCallback (GLFWwindow *window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (action == GLFW_PRESS) {
			double x, y;
			glfwGetCursorPos(window, &x, &y);
			scene->camera->activate(static_cast<float>(x), static_cast<float>(y));
		}
		else if (action == GLFW_RELEASE)
		{
			scene->camera->deactivate();
		}
	}	
}

void mouseScrollCallback (GLFWwindow *window, double xoffset, double yoffset)
{
	scene->updateFovY(scene->fovy - static_cast<float>(yoffset));	
}

void resizeCallback (GLFWwindow *window, int width, int height)
{
	scene->resize(width, height);
	glfwSetWindowTitle(window, ("uGLy Renderer (" + std::to_string(scene->windowWidth) + "x" + std::to_string(scene->windowHeight) + ")").c_str());	
}

void dropCallback(GLFWwindow *window, int count, const char **paths)
{	
	auto importedMeshes = viewer->import(paths[0]);
	if (importedMeshes.size() > 0)
	{		
		for (auto mesh : importedMeshes)
		{
			uGLy::Shader vertexShader, fragmentShader;
			vertexShader.CreateShaderFromFile(GL_VERTEX_SHADER, "./shaders/blinn-phong.vs");
			fragmentShader.CreateShaderFromFile(GL_FRAGMENT_SHADER, "./shaders/blinn-phong.fs");
			mesh->renderingProgram.AttachShader(vertexShader);
			mesh->renderingProgram.AttachShader(fragmentShader);
			mesh->renderingProgram.Link();			
			scene->meshes.push_back(mesh);			
		}
	}
}

int main(int argc, char **argv)
{
	GLFWwindow *window = nullptr;
	
	glfwSetErrorCallback(errorCallback);
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW Initialization failed!" << std::endl;
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	scene = new uGLy::Scene(1280, 720);
	viewer = new Viewer();
	viewer->scene = scene;

	//hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
	
	window = glfwCreateWindow(scene->windowWidth, scene->windowHeight, ("uGLy Renderer (" + std::to_string(scene->windowWidth) + "x" + std::to_string(scene->windowHeight) + ")").c_str(), nullptr, nullptr);
	if (!window) {
		std::cout << "GLFW window creation failed!" << std::endl;
		glfwTerminate();
		std::cin.ignore();
		return EXIT_FAILURE;
	}

	GLFWcursor *cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
	glfwSetCursor(window, cursor);

	//callbacks
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetDropCallback(window, dropCallback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGL()) {
		std::cout << "GLAD initialization error!" << std::endl;
		std::cin.get();
		glfwDestroyWindow(window);
		glfwTerminate();
		return EXIT_FAILURE;
	}
	else {
		std::cout << "Currently running OpenGL " << GLVersion.major << "." << GLVersion.minor << std::endl;
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glDebugMessageCallback(openglErrorCallback, nullptr);
		glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
	}

	glfwGetFramebufferSize(window, &scene->windowWidth, &scene->windowHeight);
	glViewport(0, 0, scene->windowWidth, scene->windowHeight);
	
	glfwSetWindowTitle(window, ("uGLy Renderer (" + std::to_string(scene->windowWidth) + "x" + std::to_string(scene->windowHeight) + ")").c_str());
	glfwSwapInterval(1);

	//defaults
	glClearDepthf(1.0f);
	glDepthFunc(GL_LESS);
	glDepthRangef(0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
		
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	//
	
	glEnable(GL_MULTISAMPLE);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);	

	uGLy::Camera *camera = new uGLy::ArcballCamera();
	camera->initialize(glm::vec3(0.0f, 5.0f, 10.0f));
	scene->addCamera(camera);

	// Load the mesh for the light
	std::vector<uGLy::Mesh*> lightMesh = viewer->import("meshes\\ico.obj");
	if (lightMesh.size() > 0)
	{
		uGLy::Shader vertexShader, fragmentShader;
		vertexShader.CreateShaderFromFile(GL_VERTEX_SHADER, "./shaders/blinn-phong.vs");
		fragmentShader.CreateShaderFromFile(GL_FRAGMENT_SHADER, "./shaders/blinn-phong.fs");
		lightMesh.at(0)->renderingProgram.AttachShader(vertexShader);
		lightMesh.at(0)->renderingProgram.AttachShader(fragmentShader);
		lightMesh.at(0)->renderingProgram.Link();
		scene->pointLight.mesh = lightMesh.at(0);
		scene->meshes.push_back(scene->pointLight.mesh);
	}

	// Light properties
	scene->pointLight.position = glm::vec3(5.0f, 5.0f, 10.0f);
	scene->pointLight.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	scene->pointLight.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
	scene->pointLight.specular = glm::vec3(1.0f, 1.0f, 1.0f);
	scene->pointLight.kconstant = 1.0f;
	scene->pointLight.klinear = 0.007f;
	scene->pointLight.kquadratic = 0.0002f;
	
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		double currentTime = glfwGetTime();
		double deltaTime = currentTime - lastTime;
		
		cameraSpeed = 1000000.0f * static_cast<float>(deltaTime);
		viewer->render(currentTime);
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastTime = glfwGetTime();
	}
	
	scene->clear();
	delete scene;
	delete viewer;
	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}