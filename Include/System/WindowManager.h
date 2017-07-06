#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H


//
// Notes:
//	- When using GLEW, ensure all #include-s are done before opengl #include-s
//	
//



#include <GL/glew.h>
#include <GL/GL.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>



#include "System/Platform.h"
#include "Util/Singleton.h"
#include "Util/Interfaces/Manager.h"
#include "Rendering/LoadShader.h"


class EROS_API CWindowManager
	: public CSingleton<CWindowManager>, public Interface::IManager
{ 

public:
	

	void StartUp() override;
	void ShutDown() override;


	GLFWwindow* GetWindow() const { return m_window; }




private:
	
	bool CreateNewWindow();


	GLFWwindow* m_window;
	int m_height;
	int m_width;

};



#endif /* WINDOWMANAGER_H */