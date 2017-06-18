#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#pragma once 

#include <iostream>
#include <stdio.h>
#include "System/Platform.h"
#include "Util/Singleton.h"
#include "Util/Interfaces/Manager.h"

class EROS_API CLogManager
: public CSingleton <CLogManager>, public Interface::IManager
{
	// To give access to private/protected members of non-copyable
	friend class CSingleton < CLogManager >;

public:
	void StartUp()  override;
	void ShutDown() override;

};

//extern CLogManager& g_LogManager;


#endif 