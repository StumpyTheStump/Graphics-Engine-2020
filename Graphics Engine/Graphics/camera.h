#pragma once
#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
class camera
{
	void processInput(GLFWwindow* window);

	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;
	glm::mat4 view;

};

