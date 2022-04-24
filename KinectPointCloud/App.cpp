#include "App.h"
#include "Shader.h"

App::App(Window* window, Kinect* kinect) :
	m_window(window),
	m_kinect(kinect)
{
	gladLoadGL();

	glViewport(0, 0, m_window->Width(), m_window->Height());
	m_shaderProgram = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &srcVertexShader, nullptr);
	glCompileShader(vertexShader);
	glAttachShader(m_shaderProgram, vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &srcFragmentShader, nullptr);
	glCompileShader(fragmentShader);
	glAttachShader(m_shaderProgram, fragmentShader);

	glLinkProgram(m_shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glGenVertexArrays(1, m_vao);
	glGenBuffers(2, m_vbo);

	glBindVertexArray(m_vao[0]);

	glPointSize(2.0f);

	m_locationMVP = glGetUniformLocation(m_shaderProgram, "mvp");

}

void App::Run()
{
	m_kinect->Start();
	Camera* camera;

	while (m_window->IsRunning())
	{
		m_kinect->Capture();

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glm::vec3 cameraPosition = camera->Instance()->Position();
		glm::mat4 view = camera->Instance()->View(cameraPosition);
		glm::mat4 projection = glm::perspective(glm::radians(50.0f), m_window->Aspect(), 0.1f, 100.0f);

		glUseProgram(m_shaderProgram);
		glUniformMatrix4fv(m_locationMVP, 1, GL_FALSE, glm::value_ptr(projection * view));

		// Point Cloud Vertex send to GPU.
		short* pointCloudBuffer = m_kinect->PointCloudBuffer();
		uint32_t pointCloudSize = m_kinect->PointCloudSize();

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, pointCloudSize * sizeof(short), pointCloudBuffer, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_SHORT, GL_FALSE, 3 * sizeof(short), nullptr);
		glEnableVertexAttribArray(0);

		// Point Cloud Color send to GPU
		image colorBuffer = m_kinect->ColorBuffer();
		
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, colorBuffer.get_size() * sizeof(uint8_t), colorBuffer.get_buffer(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_FALSE, 4 * sizeof(uint8_t), nullptr);
		glEnableVertexAttribArray(1);

		glDrawArrays(GL_POINTS, 0, pointCloudSize);

		glBindVertexArray(0);

		m_window->RenderWindow();
	}
}