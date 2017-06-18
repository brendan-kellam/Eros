#ifndef GAME_H 
#define GAME_H


#include "System/Platform.h"
#include "System/LogManager.h"

#include <iostream>

class EROS_API CGame
{
public:
	CGame();
	~CGame();

private:
	void InitSystems();
	void ShutdownSystems();

};



#endif
