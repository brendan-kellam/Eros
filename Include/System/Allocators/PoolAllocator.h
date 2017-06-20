#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#pragma once

#include <iostream>
#include "System/Platform.h"
#include "System/Allocators/Allocator.h"

class EROS_API CPoolAllocator final
	: public CAllocator
{

private:
	typedef unsigned int    uint;
	typedef unsigned char   uchar;

public:
	//void Create(uint allocatedSize, uchar* memStart) override;
	
	void Destroy() override;
	void Create(uint numOfBlock, uint blockSize, uchar* memStart);

private:
	
	uint IndexFromAddr(const uchar* addr) const;
	uchar* AddrFromIndex(uint index) const;

	void* Allocate() override;
	void  DeAllocate(void* p) override;

private:

	uint m_numOfBlocks;
	uint m_blockSize;
	uint m_numFreeBlocks;
	uint m_numInitialized;

	uchar* m_memStart;
	uchar* m_memEnd;
	uchar* m_next;

};


#endif /* POOLALLOCATOR_H */
