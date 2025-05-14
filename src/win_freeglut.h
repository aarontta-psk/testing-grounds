#pragma once
#ifndef WIN_GLUT_H
#define WIN_GLUT_H

class WinFreeGLUT {
public:
	WinFreeGLUT();
	~WinFreeGLUT();

private:
	int windowID;
	static float r, g, b;

	//static void close_callback(GLFWwindow* window);
	static void key_callback(unsigned char key, int x, int y);
	static void resize_callback(int newWidth, int newHeight);
	static void display_callback();
	static void update_callback();
};
#endif // WIN_GLFW_H