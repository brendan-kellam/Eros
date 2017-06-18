#ifndef SINGLETON_H
#define SINGLETON_H

#pragma 

#include "System/Platform.h"
#include "Util/Interfaces/NonCopyable.h"

template <typename T>
class EROS_API CSingleton : Interface::INonCopyable
{

public:
	static T& Instance()
	{
		static T instance;
		return instance;
	}

protected:
	explicit CSingleton<T>() { }

};


#endif