#include "camera.h"

//glm::mat4 projection = glm::perspective(glm::radians(90.0f), 16 / 9.0f, 0.1f, 100.0f);
//
//glm::mat4 model = glm::mat4(1);
//
//const float radius = 10.0f;
//float camX = sin(glfwGetTime() * radius);
//float camZ = cos(glfwGetTime() * radius);
//
//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
//
//glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
//
//glm::vec3 camreaTarget = glm::vec3(0.0f, 0.0f, 0.0f);
//glm::vec3 cameraDirection = glm::normalize(cameraPos - camreaTarget);
//
//glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

void camera::update(float deltaTime)
{
}

void camera::setSpeed(float speed)
{
}

void camera::setPerspective(float fieldOfView, float apsectRatio, float, float)
{
}

void camera::setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
}

void camera::setPosition(glm::vec3 position)
{
}

void camera::getWorldTransform(glm::mat4)
{
}

void camera::getView(glm::mat4)
{
}

void camera::getProjection(glm::mat4)
{
}

void camera::getProjectionView(glm::mat4)
{
}

void camera::updateProjectionViewTransform()
{
}

void camera::processInput(GLFWwindow* window)
{
	const float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

	void camera::getView(glm::mat4)
	{
	}

	void camera::getProjection(glm::mat4)
	{
	}

	void camera::getProjectionView(glm::mat4)
	{
	}

	void camera::updateProjectionViewTransform()
	{
	}

	void camera::processInput(GLFWwindow* window)
	{
		/*const float cameraSpeed = 0.05f;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/
	}