
/* Includes */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtx/transform.hpp>

#include "System/WindowManager.h"
#include "System/ResourceManager.h"
#include "Rendering/LoadShader.h"
#include "Rendering/LoadTexture.h"



/* Create window */
void CWindowManager::StartUp()
{
	m_width = 1024;
	m_height = 768;


	// Create a new GLFW window
	EROS_TRAP(CreateNewWindow());

	GLuint VertextArrayID;
	glGenVertexArrays(1, &VertextArrayID);
	glBindVertexArray(VertextArrayID);

	// array of verticies representing a triangle
	static const GLfloat g_vertex_buffer_data[] = 
	{
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,
	};

	// Identifies our vertex buffer
	GLuint vertexbuffer;

	// Generate 1 buffer. Put ID in vertexBuffer
	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);

	// Give our vertices to OpenGL
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertexBufferCube), g_vertexBufferCube, GL_STATIC_DRAW);
	 
	// random seed
	srand( (unsigned int) time(NULL) );

	// Random color lambda
	auto randColor = []() { return (GLfloat) (rand() % 255); };



	// Loop each vertex
	for (int v = 0; v < 12 * 3; v++)
	{
		g_colorBufferCube[3 * v + 0] = 255; // R
		g_colorBufferCube[3 * v + 1] = 0; // G
		g_colorBufferCube[3 * v + 2] = 0; // B
	}


	// Add color buffer to vertexes
	/*GLuint colorBuffer; 
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_colorBufferCube), g_colorBufferCube, GL_STATIC_DRAW);
*/
	
	GLuint textureBuffer;
	glGenBuffers(1, &textureBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uvBufferCube), g_uvBufferCube, GL_STATIC_DRAW);

/*
	GLuint programID = LoadShaders("C:\\Users\\brendan\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleVertexShader.vertexshader",
		"C:\\Users\\brendan\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleFragmentShader.fragmentshader");
*/


	GLuint programID = LoadShaders("C:\\Users\\brendan\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleTexture.vertexshader",
		"C:\\Users\\brendan\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleTexture.fragmentshader");


	// Projection matrx: 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), (float)m_width / (float)m_height, 0.1f, 100.0f);

	// Camera matrix
	glm::mat4 viewMatrix = glm::lookAt(
		glm::vec3(4, 3, -3),					// Camera is @ (4, 3, -3) in world space
		glm::vec3(0, 0, 0),					// Looking at the origin
		glm::vec3(0, 1, 0)					// Defines "up"
	);

	// Model matrix
	glm::mat4 modelMatrix = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f)) * glm::mat4(1.0f); // (Model will be @ the origin for now)


	glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
	// NOTE: A mvp matrix must be done for each model that is to be rendered

	
	GLuint matrixID = glGetUniformLocation(programID, "MVP");

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the color and depth buffers
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);				// Draw blue background

		// Use our shader
		glUseProgram(programID);
	
		// Send our transformation to the currently bound shader, in the "MVP" uniform
		// This is done in the main loop since each model will have a different MVP matrix (At least for the M part)
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &mvpMatrix[0][0]);


		// 1st attribute buffer : vertexes
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,					 // Attribute 0. This value is arbitrary, but MUST match the layout in the shader
			3,					 // Size
			GL_FLOAT,			 // type
			GL_FALSE,			 // normalized?
			0,					 // stride
			(void*) nullptr		 // array buffer offset
		);


		// 2nd attribute buffer : textures
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, textureBuffer);
		glVertexAttribPointer(
			1,					// Attribute
			2,					// 2
			GL_FLOAT,			// type
			GL_FALSE,			// normalized?
			0,					// stride
			(void*) nullptr		// array buffer offset
		);


		// Draw the triangles that make up the object
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0;
		glDisableVertexAttribArray(0);

		// swap buffers
		glfwSwapBuffers(m_window);	// Swap front and back buffers for specified window
		glfwPollEvents();			// Process all pending events

	} while (glfwGetKey(m_window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(m_window) == 0);


}

bool CWindowManager::CreateNewWindow()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // make osx happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Gives us new OpenGL


																   /// Open a window and create it's OpenGL context
	m_window = glfwCreateWindow(m_width, m_height, "Eros Engine", NULL, NULL);
	if (m_window == nullptr)
	{
		std::cout << "Failed to open GLFW window" << std::endl;
		glfwTerminate();
		return false; 
	}


	// Opengl Context creation
	glfwMakeContextCurrent(m_window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to init GLEW" << std::endl;
		return false;
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	return true;
}



void CWindowManager::ShutDown()
{
	

}



