#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"
#include <iostream>

class Window
{
public:
	Window(const char* title);
	~Window();

	bool IsRunning();
	void RenderWindow();

	int Width() const { return m_width; }
	int Height() const { return m_height; }
	float Aspect() const { return (float)m_width / m_height; }

private:
	GLFWwindow* m_glfwWindow;

	int m_width = 1280;
	int m_height = 720;

};
