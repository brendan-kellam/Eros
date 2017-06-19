//TODO: Rename file!

#ifndef POOL_H
#define POOL_H

#pragma once

#include <stdint.h>


class CPool
{
	typedef uint32_t		uint;
	typedef unsigned char   uchar;

	uint m_numOfBlocks;
	uint m_sizeOfEachBlock;
	uint m_numFreeBlocks; 
	uint m_numInitialized;

	uchar* m_memStart; 
	uchar* m_next;


public:

	CPool()
	{
		m_numOfBlocks = 0;
		m_sizeOfEachBlock = 0;
		m_numFreeBlocks = 0;
		m_numInitialized = 0;
		m_memStart = nullptr;
		m_next = nullptr;
	}

	void CreatePool(size_t sizeOfEachBlock, uint numOfBlocks)
	{
		m_numOfBlocks = numOfBlocks;
		m_sizeOfEachBlock = sizeOfEachBlock;
		m_memStart = new uchar[m_sizeOfEachBlock * m_numOfBlocks];

		m_numFreeBlocks = numOfBlocks;
		m_next = m_memStart;
	}
	
	void* Allocate()
	{
		if (m_numInitialized < m_numOfBlocks)
		{

		}
	}



};




#endif /* POOL_H */
