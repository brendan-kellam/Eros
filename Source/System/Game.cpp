
#include "System/Game.h"
#include "System/MemoryManager.h"
#include "System/WindowManager.h"
#include "System/ResourceManager.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

CGame::CGame()
{


	InitSystems();
}

CGame::~CGame()
{ 
	ShutdownSystems();
}


/* Initialization of all Engine systems */
void CGame::InitSystems()
{
	
	CMemoryManager			::Instance().StartUp();
	CResourceManager		::Instance().StartUp();
	CLogManager				::Instance().StartUp();
	CWindowManager			::Instance().StartUp();
}

void CGame::ShutdownSystems()
{
	CWindowManager			::Instance().ShutDown();
	CLogManager				::Instance().ShutDown();
	CResourceManager		::Instance().ShutDown();
	CMemoryManager			::Instance().ShutDown();
}

