#include "win_freeglut.h"

#define GLFW_INCLUDE_NONE

#include <iostream>
#include <thread>
#include <chrono>

#include <GL/freeglut.h>

float WinFreeGLUT::r = 0.2f;
float WinFreeGLUT::g = 0.3f;
float WinFreeGLUT::b = 0.3f;

void WinFreeGLUT::key_callback(unsigned char key, int x, int y)
{
	if (key == 27)
		glutLeaveMainLoop();  // stops main loop and destroy the OpenGL context
}

void WinFreeGLUT::display_callback() {
	glClearColor(r, g, b, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// new color
	r = (rand() % 11) / 10.0f;
	g = (rand() % 11) / 10.0f;
	b = (rand() % 11) / 10.0f;

	std::this_thread::sleep_for(std::chrono::milliseconds(200));

	glutSwapBuffers();	// swaps the front and back buffer
}

void WinFreeGLUT::resize_callback(int newWidth, int newHeight)
{
	// adjust viewport to match new window dimensions
	glViewport(0, 0, newWidth, newHeight);
}

void WinFreeGLUT::update_callback()
{
	glutPostRedisplay();
}

WinFreeGLUT::WinFreeGLUT() {
	// initialise FreeGLUT framework
	int argc = 0;
	glutInit(&argc, nullptr);
	//if (!glutInit(nullptr, nullptr)) {
	//	std::cout << "epic fail in the GLUT initialisation.";
	//	exit(EXIT_FAILURE);
	//}

	// add context flags before creation
	glutInitContextVersion(3, 2);
	glutInitContextFlags(GLUT_DEBUG);			// GLUT_FORWARD_COMPATIBLE
	glutInitContextProfile(GLUT_CORE_PROFILE);  // GLUT_COMPATIBILITY_PROFILE

	// add window configs before creation
	glutInitWindowSize(640, 480);								// window size
	glutInitWindowPosition(200, 200);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);	// RGBA colors, double buffer, depth buffer (GLUT_STENCIL, stencil buffer)

	// create GLFW window
	if (!(windowID = glutCreateWindow("OpenGL FreeGLUT Triangle"))) {
		std::cout << "epic fail in the GLFW windowcreation.";
		glutLeaveMainLoop();
		exit(EXIT_FAILURE);
	}

	// set error, close and key callbacks to handle each of these events
	glutReshapeFunc(resize_callback);
	glutKeyboardFunc(key_callback);
	glutDisplayFunc(display_callback);
	glutIdleFunc(update_callback);

	// enters the main event processing loop 
	glutMainLoop();      
}

WinFreeGLUT::~WinFreeGLUT() {
	// stops main loop and destroy the OpenGL context
	glutLeaveMainLoop();
}