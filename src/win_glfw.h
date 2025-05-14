#pragma once
#ifndef WIN_GLFW_H
#define WIN_GLFW_H

struct GLFWwindow;

class WinGLFW {
public:
	WinGLFW();
	~WinGLFW();

	void run();

private:
	GLFWwindow* window;

	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void close_callback(GLFWwindow* window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};
#endif // WIN_GLFW_H