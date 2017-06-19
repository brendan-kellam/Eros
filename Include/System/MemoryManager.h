#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#pragma once

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#include "System/Platform.h"
#include "Util/Interfaces/Manager.h"
#include "Util/Singleton.h"
#include "Util/BasicProfiler.h"

// Defines the amount of memory that is allocated on initialization of the game
#define MEMORY_ALLOCATION_SIZE_MB 1024
#define MB_TO_B_SCALE 1000000
#define MB_TO_GB_SCALE 0.001

#define MEMORY_STACK_PARTITION 1024*4


class EROS_API CMemoryManager final
	: public CSingleton<CMemoryManager>, public Interface::IManager 
{

public:

	void StartUp()  override;
	void ShutDown() override;


private:
	void* m_point;

};



#endif /* MEMORYMANAGER_H */