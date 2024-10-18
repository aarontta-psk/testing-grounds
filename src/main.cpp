#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

#include <GLFW/glfw3.h>


void close_callback(GLFWwindow* window) {

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}


int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// error
	glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		return 0;
	}

	GLFWwindow* window = glfwCreateWindow(640, 480, "lmao", NULL, NULL);
	// Window or OpenGL context creation failed
	if (!window) {
		glfwTerminate();
		return 0;
	}

	// OpenGL context
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// input
	glfwSetKeyCallback(window, key_callback);
	// close
	glfwSetWindowCloseCallback(window, close_callback);

	// main loop
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	_CrtDumpMemoryLeaks(); // Check for memory leaks
}