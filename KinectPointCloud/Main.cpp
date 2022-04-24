#include <iostream>
#include "Window.h"
#include "App.h"
#include "Camera.h"

Camera* Camera::m_instance = nullptr;

int main()
{
	Window window{"Point Cloud View"};
	Kinect kinect;
	App app(&window, &kinect);

	app.Run();
}