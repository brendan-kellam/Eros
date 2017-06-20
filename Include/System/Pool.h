//TODO: Rename file!

#ifndef POOL_H
#define POOL_H

#pragma once


#include "System/Platform.h"
#include <stdint.h>


class EROS_API CPool
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

	~CPool()
	{
		DestroyPool();
	}

	void CreatePool(size_t sizeOfEachBlock, uint numOfBlocks)
	{
		m_numOfBlocks = numOfBlocks;
		m_sizeOfEachBlock = sizeOfEachBlock;
		m_memStart = new uchar[m_sizeOfEachBlock * m_numOfBlocks];

		m_numFreeBlocks = numOfBlocks;
		m_next = m_memStart;
	}

	void DestroyPool()
	{
		delete[] m_memStart;
		m_memStart = nullptr;
	}

	uchar* AddrFromIndex(uint index) const 
	{
		return m_memStart + (index * m_sizeOfEachBlock);
	}

	uint IndexFromAddr(const uchar* addr) const
	{
		return (((uint)(addr - m_memStart)) / m_sizeOfEachBlock);
	}
	
	void* Allocate()
	{
		if (m_numInitialized < m_numOfBlocks)
		{
			uint* p = (uint*)AddrFromIndex(m_numInitialized);
			*p = m_numInitialized + 1;
			m_numInitialized++; 
		}

		void* ret = nullptr;
		if (m_numFreeBlocks > 0)
		{
			ret = (void*)m_next;
			--m_numFreeBlocks;
			if (m_numFreeBlocks != 0)
			{
				m_next = AddrFromIndex( *( (uint*) m_next ) );
			}
			else
			{
				m_next = nullptr;
			}
		}

		return ret;
	}

	void DeAllocate(void* p)
	{
		if (m_next != nullptr)
		{
			(*(uint*)p) = IndexFromAddr(m_next);
			m_next = (uchar*)p;
		}
		else
		{
			*((uint*)p) = m_numOfBlocks;
			m_next = (uchar*)p;
		}
		++m_numFreeBlocks;
	}

};




#endif /* POOL_H */
