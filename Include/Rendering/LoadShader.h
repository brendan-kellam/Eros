#ifndef LOADSHADER_H
#define LOADSHADER_H

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "System/Platform.h"

// Load shaders function
GLuint LoadShaders(std::string vertex_file_path, std::string fragment_file_path);
bool ReadFromShader(std::ifstream& stream, std::string& output);
void CompileShader(GLuint shaderID, std::string& shaderCode);

#endif /* LOADSHADER_H */
