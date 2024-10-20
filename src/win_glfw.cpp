#include "win_glfw.h"

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <thread>
#include <chrono>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

void WinGLFW::error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void WinGLFW::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void WinGLFW::close_callback(GLFWwindow* window) {
	std::cout << "epic window closing.";
}

void WinGLFW::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// adjust viewport to match new window dimensions
	glViewport(0, 0, width, height);
}

WinGLFW::WinGLFW() {
	// initialise GFLW framework
	if (!glfwInit()) {
		std::cout << "epic fail in the GLFW initialisation.";
		exit(EXIT_FAILURE);
	}

	// add window flags before creation
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create GLFW window
	if (!(window = glfwCreateWindow(640, 480, "OpenGL GLFW Triangle", NULL, NULL))) {
		std::cout << "epic fail in the GLFW windowcreation.";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// set error, close and key callbacks to handle each of these events
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetWindowCloseCallback(window, close_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// add OpenGL context to the current GLFW window
	glfwMakeContextCurrent(window);

	// use GLAD loader to load OpenGL directives
	gladLoadGL(glfwGetProcAddress);
}

WinGLFW::~WinGLFW() {
	// remove GLFW window
	glfwDestroyWindow(window);
	// terminate GLFW framework
	glfwTerminate();
}

void WinGLFW::run() {
	float r, g, b;
	r = 0.2f; g = 0.3f; b = 0.3f;
	// main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(r, g, b, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// new color
		r = (rand() % 11) / 10.0f;
		g = (rand() % 11) / 10.0f;
		b = (rand() % 11) / 10.0f;

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}