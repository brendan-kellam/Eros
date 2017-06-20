

#include "System/Allocators/PoolAllocator.h"


void CPoolAllocator::Create(uint numOfBlock, uint blockSize, uchar* memStart)
{
	std::cout << "Creating new pool allocator..." << std::endl;

	// Asserts
	EROS_TRAP(m_memStart == nullptr);
	EROS_TRAP(memStart != nullptr);
	
	EROS_TRAP(m_partitionSize == 0);
	EROS_TRAP(numOfBlock >= 0);
	EROS_TRAP(blockSize >= 0);
	
	m_memStart	    = memStart;
	m_numOfBlocks   = numOfBlock;
	m_blockSize		= blockSize;
	m_partitionSize = numOfBlock * blockSize;
	m_memEnd		= m_memStart + m_partitionSize;

	m_numFreeBlocks = m_numOfBlocks;
	m_numInitialized = 0;
	
	std::cout << "POOL: memory_start: " << (uint) m_memStart << std::endl;
	std::cout << "POOL: partition_size: " << m_partitionSize << std::endl;
	std::cout << "POOL: memory_end: " << (uint) m_memEnd << std::endl;

	m_next = m_memStart;
}

CPoolAllocator::uchar* CPoolAllocator::AddrFromIndex(uint index) const
{
	return m_memStart + (index * m_blockSize);
}

CPoolAllocator::uint CPoolAllocator::IndexFromAddr(const uchar* addr) const
{
	return (((uint)(addr - m_memStart)) / m_blockSize);
}

void* CPoolAllocator::Allocate()
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
			m_next = AddrFromIndex(*((uint*)m_next));
		}
		else
		{
			m_next = nullptr;
		}
	}

	return ret;
}

void CPoolAllocator::DeAllocate(void* p)
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



void CPoolAllocator::Destroy()
{
	m_memStart = nullptr;
	m_memEnd   = nullptr;
	m_next     = nullptr;
}

