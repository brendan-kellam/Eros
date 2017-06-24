
#include "Rendering/LoadShader.h"

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);


	// Read the Vertex Shader code from file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);


	if (!ReadFromShader(VertexShaderStream, VertexShaderCode))
	{
		std::cout << "ERROR: Unable to open Vertex shader. Path: " << vertex_file_path << "." << std::endl;
		return 0;
	}

	// Read Fragment shader
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);

	if (!ReadFromShader(FragmentShaderStream, FragmentShaderCode))
	{
		std::cout << "ERROR: Unable to open Fragment shader. Path: " << fragment_file_path << "." << std::endl;
		return 0;
	}

	// Compile vertex shader
	CompileShader(VertexShaderID, VertexShaderCode);


	// Compile fragment shader
	CompileShader(FragmentShaderID, FragmentShaderCode);


	// Link the program
	GLint result = GL_FALSE;
	int infoLogLength;

	std::cout << "Linking program.." << std::endl; 
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << std::endl;
	}


	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void CompileShader(GLuint shaderID, std::string& shaderCode)
{
	char const* pShaderCode = shaderCode.c_str();
	glShaderSource(shaderID, 1, &pShaderCode, NULL);
	
	// Compile shader
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int infoLogLength;

	// Check Shader validity 
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cout << &shaderErrorMessage[0] << std::endl;
	}
}


bool ReadFromShader(std::ifstream& stream, std::string& output)
{
	if (!stream.is_open())
	{
		return false;
	}
	else
	{
		std::string line;
		while (getline(stream, line))
		{
			output += '\n' + line;
		}

		stream.close();
	}
}