#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Window.h"
#include "Kinect.h"
#include "Camera.h"

class App
{
public:
	App(Window* window, Kinect* kinect);
	//~App();

	void Run();

private:
	Window* m_window;
	Kinect* m_kinect;

	GLuint m_shaderProgram;
	GLuint m_vao[1];
	GLuint m_vbo[2]; // 0: vertex, 1: color
	GLuint m_locationMVP;
};

