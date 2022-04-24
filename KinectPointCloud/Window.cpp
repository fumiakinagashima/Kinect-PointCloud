#include "Window.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

Window::Window(const char* title):
	m_glfwWindow(nullptr)
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);

	m_glfwWindow = glfwCreateWindow(m_width, m_height, title, nullptr, nullptr);

	glfwMakeContextCurrent(m_glfwWindow);

	// For Input events.
	glfwSetKeyCallback(m_glfwWindow, key_callback);
	glfwSetCursorPosCallback(m_glfwWindow, cursor_position_callback);
	glfwSetMouseButtonCallback(m_glfwWindow, mouse_button_callback);
	glfwSetScrollCallback(m_glfwWindow, scroll_callback);
}

Window::~Window()
{
	glfwTerminate();
	glfwDestroyWindow(m_glfwWindow);
}

bool Window::IsRunning()
{
	return !glfwWindowShouldClose(m_glfwWindow);
}

void Window::RenderWindow()
{
	glfwSwapBuffers(m_glfwWindow);
	glfwPollEvents();
}

/***
* Input Controller
 ***/
double g_prevXpos = 0.0f;
double g_prevYpos = 0.0f;

bool g_pressingMLB = false;
bool g_pressingMRB = false;
bool g_pressingMMB = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	Camera* camera;
	if (key == GLFW_KEY_RIGHT) camera->Instance()->SetTheta(1.0f);
	if (key == GLFW_KEY_LEFT) camera->Instance()->SetTheta(-1.0f);
	if (key == GLFW_KEY_DOWN) camera->Instance()->SetRadial(0.1f);
	if (key == GLFW_KEY_UP) camera->Instance()->SetRadial(-0.1f);
	if (key == GLFW_KEY_PAGE_UP) camera->Instance()->SetPhi(0.2f);
	if (key == GLFW_KEY_PAGE_DOWN) camera->Instance()->SetPhi(-0.2f);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	Camera* camera;
	std::cout << "xpos: " << xpos << " ypos:" << ypos << std::endl;
	if (g_pressingMLB)
	{
		// Holizon rotation
		if (xpos - g_prevXpos > 0) camera->Instance()->SetTheta(-2.0f);
		else if (xpos - g_prevXpos < 0) camera->Instance()->SetTheta(2.0f);

		// Vertical rotation
		if (ypos - g_prevYpos > 0) camera->Instance()->SetPhi(0.3f);
		else if (ypos - g_prevYpos < 0) camera->Instance()->SetPhi(-0.3f);
	}
	g_prevXpos = xpos;
	g_prevYpos = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	std::cout << "button: " << button << " action:" << action << std::endl;
	switch (button)
	{
		case GLFW_MOUSE_BUTTON_LEFT:
		{
			if (action == GLFW_PRESS) g_pressingMLB = true;
			else if (action == GLFW_RELEASE) g_pressingMLB = false;
		}
		break;

		case GLFW_MOUSE_BUTTON_RIGHT:
		{
			if (action == GLFW_PRESS) g_pressingMRB = true;
			else if (action == GLFW_RELEASE) g_pressingMRB = false;
		}
		break;

		case GLFW_MOUSE_BUTTON_MIDDLE:
		{
			if (action == GLFW_PRESS) g_pressingMMB = true;
			else if (action == GLFW_RELEASE) g_pressingMMB = false;
		}
		break;
	}
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	Camera* camera;
	if (yoffset > 0) camera->Instance()->SetRadial(-0.5f);
	else camera->Instance()->SetRadial(0.5f);
}