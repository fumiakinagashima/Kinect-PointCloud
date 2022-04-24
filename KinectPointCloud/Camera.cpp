#include "Camera.h"

Camera::Camera()
{}

Camera* Camera::Instance()
{
	if (m_instance == nullptr) m_instance = new Camera();
	return m_instance;
}

glm::vec3 Camera::Position()
{
	return glm::vec3(
		glm::sin(glm::radians(m_theta)) * m_radial,
		m_phi,
		glm::cos(glm::radians(m_theta)) * m_radial);
}

glm::mat4 Camera::View(glm::vec3 cameraPosition)
{
	return glm::lookAt(cameraPosition, m_destination, glm::vec3(0.0f, 1.0f, 0.0f));
} 