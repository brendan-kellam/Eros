
#include "System/WindowManager.h"



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
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	GLuint programID = LoadShaders("C:\\Users\\poptart\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleVertexShader.vertexshader", 
		"C:\\Users\\poptart\\Documents\\c++\\Eros\\Resources\\Shaders\\SimpleFragmentShader.fragmentshader");
	

	do {

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

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

		// Draw the triangle
		glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0;
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

	return true;
}



void CWindowManager::ShutDown()
{
	

}



