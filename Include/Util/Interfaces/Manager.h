#ifndef MANAGERINTERFACE_H
#define MANAGERINTERFACE_H

#pragma once

#include "System/Platform.h"

namespace Interface
{
	class EROS_API IManager
	{
	public:
		virtual void StartUp() = 0;
		virtual void ShutDown() = 0;

	};
}



#endif