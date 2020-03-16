#include "glm.hpp"
#include "gl_core_4_5.h"
#include "glfw3.h"
#include "ext.hpp"
#include <fstream>
#include <sstream>
#include "camera.h"
#include "OBJMesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


using uint = unsigned int;

uint loadTexture(std::string filename)
{
	uint m_texture;
	int x, y, n;
	unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 0);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel
	//glDeleteTextures(1, &m_texture));

	stbi_image_free(data);
	return m_texture;
}


struct Vertex {
	glm::vec3 position;
	glm::vec2 texCoord;
};

int main()
{

	stbi_set_flip_vertically_on_load(true);
	float r = 0.2f;
	float g = 0.2f;
	float b = 0.2f;
	float a = 1.0f;

	bool rpositive = true;
	bool gpositive = true;
	bool bpositive = true;

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

	// Create mesh data
	/*glm::vec3 verticies[] =
	{
		glm::vec3(-0.5f, 0.5f, 0.0f),
		glm::vec3( 0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, 0.5f, 0.0f),
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3( 0.5f, -0.5f, 0.0f)
	};*/
	

	Vertex verticies[] =
	{
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(0,1)} ,
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1,1)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(0,0)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0,0)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(1,1)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(1,0)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0,1)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1,1)},
	};

	int index_buffer[] { 
		1,0,2,1,2,3,  
		0,1,5,0,5,7,
		5,4,6,6,7,5,
		3,6,4,3,2,6,
		6,2,0,0,7,6,
		1,4,5,4,1,3 };

	aie::OBJMesh myMesh;
	aie::OBJMesh ballMesh;
	uint m_texture;
	int x, y, n;

	// Create and Load mesh
	uint VAO;
	uint VBO;
	uint IBO;

	unsigned char* data = stbi_load("../images/logo.jpg", &x, &y, &n, 0);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &IBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, 36 * sizeof(Vertex), verticies, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 * sizeof(int), index_buffer, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(glm::vec3));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // GL_LINEAR SAMPLES texels
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // GL_NEARESTS RETURNS just closest pixel


	/** CAMERA **/
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), 16 / 9.0f, 0.1f, 100.0f);
	
	glm::mat4 model = glm::mat4(1);
	glm::mat4 ballTransform = glm::mat4(0.01f);
	ballTransform[3][3] = 1;


	glm::mat4 dragon_tranform = glm::mat4(1);

	glm::vec3 cameraPos = glm::vec3(0.0f, 4.0f, 7.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

	uint vertex_shader_ID = 0;
	uint fragment_shader_ID = 0;
	uint shader_program_ID = 0;

	// Load shader from file into string
	std::string shader_data;
	std::ifstream in_file_stream("..\\Shaders\\texture_vert.glsl", std::ifstream::in);

	// Load the source into a string for compilation
	std::stringstream string_stream;
	if (in_file_stream.is_open())
	{
		string_stream << in_file_stream.rdbuf();
		shader_data = string_stream.str();
		in_file_stream.close();
	}

	// Allocate space for shader program
	vertex_shader_ID = glCreateShader(GL_VERTEX_SHADER);
	// Convert to raw char*
	const char* m_data = shader_data.c_str();
	// Send in the char* tp shader location
	glShaderSource(vertex_shader_ID, 1, (const GLchar**)&m_data, 0);
	// Build
	glCompileShader(vertex_shader_ID);

	// Is it working
	// Check the shader compiled
	GLint success = GL_FALSE;
	glGetShaderiv(vertex_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		// Get the length of the OpenGL error message
		GLint log_length = 0;
		glGetShaderiv(vertex_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		// Create the error buffer
		char* log = new char[log_length];
		// Copy the error from the buffer
		glGetShaderInfoLog(vertex_shader_ID, log_length, 0, log);

		// Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// Clean up anyway
		delete[] log;
	}

	/** PART2 **/
	std::ifstream in_file_stream_frag("..\\Shaders\\texture_frag.glsl", std::ifstream::in);
	bool loaded = myMesh.load("../Models/Ball.obj", false);


	
	// Load the source into a string for compilation
	std::stringstream frag_string_stream;
	if (in_file_stream_frag.is_open())
	{
		frag_string_stream << in_file_stream_frag.rdbuf();
		shader_data = frag_string_stream.str();
		in_file_stream_frag.close();
	}

	// Allocate space for shader program
	fragment_shader_ID = glCreateShader(GL_FRAGMENT_SHADER);
	// Convert to raw char*
	m_data = shader_data.c_str();
	// Send in the char* tp shader location
	glShaderSource(fragment_shader_ID, 1, (const GLchar**)&m_data, 0);
	// Build
	glCompileShader(fragment_shader_ID);

	// Is it working
	// Check the shader compiled
	success = GL_FALSE;
	glGetShaderiv(fragment_shader_ID, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		// Get the length of the OpenGL error message
		GLint log_length = 0;
		glGetShaderiv(fragment_shader_ID, GL_INFO_LOG_LENGTH, &log_length);
		// Create the error buffer
		char* log = new char[log_length];
		// Copy the error from the buffer
		glGetShaderInfoLog(fragment_shader_ID, log_length, 0, log);

		// Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// Clean up anyway
		delete[] log;
	}

	shader_program_ID = glCreateProgram();

	glAttachShader(shader_program_ID, vertex_shader_ID);
	glAttachShader(shader_program_ID, fragment_shader_ID);

	glLinkProgram(shader_program_ID);

	success = GL_FALSE;
	glGetProgramiv(shader_program_ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		// Get the length of the OpenGL error message
		GLint log_length = 0;
		glGetProgramiv(shader_program_ID, GL_INFO_LOG_LENGTH, &log_length);
		// Create the error buffer
		char* log = new char[log_length];
		// Copy the error from the buffer
		glGetProgramInfoLog(shader_program_ID, log_length, 0, log);

		// Create the error message
		std::string error_message(log);
		error_message += "SHADER_FAILED_TO_COMPILE";
		printf(error_message.c_str());
		// Clean up anyway
		delete[] log;

	}


	uint diffuse = loadTexture("../Models/football_ball_BaseColor.png");
	uint normal = loadTexture("../Models/football_ball_Normal.png");




	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	glClearColor(r, g, b, a);

	// Game Loop
	while (glfwWindowShouldClose(window) == false && 
			glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//glm::mat4 pvm = projection * view * model;
		model = glm::rotate(model, 0.01f, glm::vec3(0, 1, 0));

		glm::mat4 pv = projection * view;
		glm::mat4 world = glm::inverse(view);
		//glm::vec3 cameraPosition = { world[3][0], world[3][1], world[3][2] };
		glm::vec3 cameraPosition = glm::vec3(world[3]);

		glm::vec4 color = glm::vec4(0, 0, 0, 1);

		

		glUseProgram(shader_program_ID);
		auto uniform_location = glGetUniformLocation(shader_program_ID, "projection_view_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(pv));
		uniform_location = glGetUniformLocation(shader_program_ID, "model_matrix");
		glUniformMatrix4fv(uniform_location, 1, false, glm::value_ptr(ballTransform));
		uniform_location = glGetUniformLocation(shader_program_ID, "base_colour");
		glUniform4fv(uniform_location, 1, glm::value_ptr(color));
		uniform_location = glGetUniformLocation(shader_program_ID, "light_direction");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(-1)));

		uniform_location = glGetUniformLocation(shader_program_ID, "normal_matrix");
		glUniformMatrix3fv(uniform_location, 1, false, glm::value_ptr(glm::inverseTranspose(glm::mat3(model))));


		uniform_location = glGetUniformLocation(shader_program_ID, "light_color");
		glUniform3fv(uniform_location, 1, glm::value_ptr(glm::vec3(r, g, b)));

		uniform_location = glGetUniformLocation(shader_program_ID, "camera_position");
		glUniform3fv(uniform_location, 1, glm::value_ptr(cameraPosition));


		uniform_location = glGetUniformLocation(shader_program_ID, "specular_power");
		glUniform1f(uniform_location,32.0f);

		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		// DRAW THE BUNNY //

		// Get the uniform variables location. You've probably already done that before...
		uint decalTexLocation = glGetUniformLocation(shader_program_ID, "diffuseTexture");
		uint bumpTexLocation = glGetUniformLocation(shader_program_ID, "normalTexture");


		glUniform1i(decalTexLocation, 0);
		glUniform1i(bumpTexLocation, 1);

		glActiveTexture(GL_TEXTURE0); // Texture unit 0
		glBindTexture(GL_TEXTURE_2D, diffuse);

		glActiveTexture(GL_TEXTURE1); // Texture unit 1
		glBindTexture(GL_TEXTURE_2D, normal);

		myMesh.draw();

		if (rpositive)
			r += 0.001f;
		else
			r -= 0.001f;

		if (gpositive)
			g += 0.003f;
		else
			g -= 0.003f;

		if (bpositive)
			b += 0.005f;
		else
			b -= 0.005f;


		if (r >= 1)
			rpositive = false;
		else if (r <= 0)
			rpositive = true;

		if (g >= 1)
			gpositive = false;
		else if (g <= 0)
			gpositive = true;

		if (b >= 1)
			bpositive = false;
		else if (b <= 0)
			bpositive = true;


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}