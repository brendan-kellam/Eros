
#include "System/LogManager.h"
#include <iostream>

void CLogManager::StartUp()
{
	std::cout << "LogManager starting" << std::endl;
}

void CLogManager::ShutDown()
{
	std::cout << "LogManager stopping.." << std::endl;
}

