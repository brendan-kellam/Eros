
#include "System/Game.h"
#include "System/MemoryManager.h"

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
	CLogManager				::Instance().StartUp();

	// TEMP //
	system("pause");
}

void CGame::ShutdownSystems()
{
	CLogManager				::Instance().ShutDown();
	CMemoryManager			::Instance().ShutDown();
}

