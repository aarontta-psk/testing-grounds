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
	if (!(window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL))) {
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

		r = (rand() % 11) / 10.0f;
		g = (rand() % 11) / 10.0f;
		b = (rand() % 11) / 10.0f;

		std::this_thread::sleep_for(std::chrono::milliseconds(200));
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

//#define _CRTDBG_MAP_ALLOC
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//#include <crtdbg.h>
//

//
//
//#include "linmath.h"
//
//typedef struct Vertex
//{
//    vec2 pos;
//    vec3 col;
//} Vertex;
//
//static const Vertex vertices[3] =
//{
//    { { -0.6f, -0.4f }, { 1.f, 0.f, 0.f } },
//    { {  0.6f, -0.4f }, { 0.f, 1.f, 0.f } },
//    { {   0.f,  0.6f }, { 0.f, 0.f, 1.f } }
//};
//
//static const char* vertex_shader_text =
//"#version 330\n"
//"uniform mat4 MVP;\n"
//"in vec3 vCol;\n"
//"in vec2 vPos;\n"
//"out vec3 color;\n"
//"void main()\n"
//"{\n"
//"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
//"    color = vCol;\n"
//"}\n";
//
//static const char* fragment_shader_text =
//"#version 330\n"
//"in vec3 color;\n"
//"out vec4 fragment;\n"
//"void main()\n"
//"{\n"
//"    fragment = vec4(color, 1.0);\n"
//"}\n";
//

//
//int main(void)
//{
//    glfwSetErrorCallback(error_callback);
//
//    if (!glfwInit())
//        exit(EXIT_FAILURE);
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Triangle", NULL, NULL);
//    if (!window)
//    {
//        glfwTerminate();
//        exit(EXIT_FAILURE);
//    }
//
//    glfwSetKeyCallback(window, key_callback);
//
//    glfwMakeContextCurrent(window);
//    gladLoadGL(glfwGetProcAddress);
//    glfwSwapInterval(1);
//
//    // NOTE: OpenGL error checks have been omitted for brevity
//
//    GLuint vertex_buffer;
//    glGenBuffers(1, &vertex_buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
//    glCompileShader(vertex_shader);
//
//    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
//    glCompileShader(fragment_shader);
//
//    const GLuint program = glCreateProgram();
//    glAttachShader(program, vertex_shader);
//    glAttachShader(program, fragment_shader);
//    glLinkProgram(program);
//
//    const GLint mvp_location = glGetUniformLocation(program, "MVP");
//    const GLint vpos_location = glGetAttribLocation(program, "vPos");
//    const GLint vcol_location = glGetAttribLocation(program, "vCol");
//
//    GLuint vertex_array;
//    glGenVertexArrays(1, &vertex_array);
//    glBindVertexArray(vertex_array);
//    glEnableVertexAttribArray(vpos_location);
//    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
//        sizeof(Vertex), (void*)offsetof(Vertex, pos));
//    glEnableVertexAttribArray(vcol_location);
//    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
//        sizeof(Vertex), (void*)offsetof(Vertex, col));
//
//    while (!glfwWindowShouldClose(window))
//    {
//        int width, height;
//        glfwGetFramebufferSize(window, &width, &height);
//        const float ratio = width / (float)height;
//
//        glViewport(0, 0, width, height);
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        mat4x4 m, p, mvp;
//        mat4x4_identity(m);
//        mat4x4_rotate_Z(m, m, (float)glfwGetTime());
//        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
//        mat4x4_mul(mvp, p, m);
//
//        glUseProgram(program);
//        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
//        glBindVertexArray(vertex_array);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwDestroyWindow(window);
//
//    glfwTerminate();
//    exit(EXIT_SUCCESS);
//}