#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
class camera
{
	void update(float deltaTime);
	void setSpeed(float speed);
	void setPerspective(float fieldOfView, float apsectRatio, float near, float far);
	void setLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void setPosition(glm::vec3 position);
	void getWorldTransform(glm::mat4);
	void getView(glm::mat4);
	void getProjection(glm::mat4);
	void getProjectionView(glm::mat4);
	void updateProjectionViewTransform();

	void processInput(GLFWwindow* window);

	//glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	//glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	//glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 worldTransform;
	glm::mat4 viewTransform;
	glm::mat4 projectionTransform;
	glm::mat4 projectViewTransform;
};

