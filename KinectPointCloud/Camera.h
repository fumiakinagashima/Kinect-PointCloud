#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
public:
	Camera();

	static Camera* Instance();

	float Theta() const { return m_theta; }
	float Phi() const { return m_phi; }
	float Radial() const { return m_radial; }

	void SetTheta(float value) { m_theta += value; }
	void SetPhi(float value) { m_phi += value; }
	void SetRadial(float value) { m_radial += value; }

	glm::vec3 Position();
	glm::mat4 View(glm::vec3 cameraPosition);

private:
	static Camera* m_instance;

	float m_theta = 0.0f;
	float m_phi = 0.0f;
	float m_radial = 3.0f;

	glm::vec3 m_destination = glm::vec3(0.0f);
};

