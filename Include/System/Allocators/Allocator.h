#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#pragma

#include "System/Platform.h"
#include "Util/Interfaces/NonCopyable.h"

class EROS_API CAllocator : Interface::INonCopyable
{

public:
	//virtual void Create(unsigned int allocatedSize, unsigned char* memStart) = 0;
	virtual void Destroy() = 0;

protected:
	unsigned char* m_memStart;
	unsigned int   m_partitionSize;
	
	explicit CAllocator()
	{
		m_memStart		= nullptr;
		m_partitionSize = 0;
	}

	~CAllocator() { }

private:
	virtual void* Allocate() = 0;
	virtual void  DeAllocate(void* p) = 0;

};


#endif /* ALLOCATOR_H */
