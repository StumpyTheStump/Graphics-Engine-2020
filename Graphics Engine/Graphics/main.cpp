#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"

using uint = unsigned int;

int main()
{
	if (glfwInit() == false)
		return 1;

	// Setting window resolution
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Computer Graphics", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	// Testing the OpenGl functions
	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	auto major = ogl_GetMajorVersion();
	auto minor = ogl_GetMinorVersion();
	printf("GL: %i.%i\n", major, minor);

	//
	glm::vec3 verticies[] =
	{
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3( 0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, -0.5f, 0.0f)
	};

	glm::mat4 projection = glm::perspective(90.0f, 16 / 9.0f, 0.1f, 5.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 1), glm::vec3(1,0, 0), glm::vec3(0, 1, 0));
	glm::mat4 model = glm::mat4(1);

	glm::mat4 pvm = projection * view * model;

	for (int i = 0; i < 6; ++i)
	{
		verticies[i] = (glm::vec3)(pvm * glm::vec4(verticies[i], 1));
	}

	uint VAO;
	uint VBO;
	// int IBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


	// Keeps the window open till the Escape key is pressed
	while (glfwWindowShouldClose(window) == false && 
			glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}