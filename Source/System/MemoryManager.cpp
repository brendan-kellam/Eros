
#include "System/MemoryManager.h"

//
// Startup:	
//	Upon startup of our memory manager, we initially allocate a pre-set block of memory from the heap. 
//  (From now own, this is know as the global memory block)
//  The global block represents our total amount of dynamic memory we may use in the game. 
//  Following the initialization of the global memory block, we initialize each Allocation manager (I.E Stack, Pool etc.).
//
//  Each allocation manager must be given a pre-set partition of the global block. (We may consider having a small
//  partition kept within memory manager to act as a "rainy-day-fund" for the allocators)
//
//  The allocators are responsible for 
// 

void CMemoryManager::StartUp()
{

	std::cout << "ALLOCATION: Allocating " << MEMORY_ALLOCATION_SIZE_MB * MB_TO_GB_SCALE << " GB onto heap" << std::endl;
	

	auto t1 = EROS_TIME_NOW;

	// Allocate static-sized memory block on heap (requires user->kernal->user context switch)
	m_baseAddress = (unsigned char*) malloc(MEMORY_ALLOCATION_SIZE_MB * MB_TO_B_SCALE);
	
	// Assert memory was correctly initialized
	EROS_TRAP(m_baseAddress != nullptr);
	m_curAddress = m_baseAddress;

	auto t2 = EROS_TIME_NOW;
	auto duration = EROS_DURATION_MILLI(t1, t2);
	
	std::cout << "Heap allocation time: " << duration << " milliseconds" << std::endl;

	CreateAllocators();
}

void CMemoryManager::CreateAllocators()
{
	Pool_4Blocks_16Bytes.Create(4, 16, RequestPartition(4*16));
}

void CMemoryManager::DestroyAllocators()
{
	Pool_4Blocks_16Bytes.Destroy();
}

unsigned char* CMemoryManager::RequestPartition(unsigned int size)
{
	unsigned char* temp = m_curAddress;
	m_curAddress = m_baseAddress + size;
	return temp;
}

void CMemoryManager::ShutDown()
{
	int  size = MEMORY_ALLOCATION_SIZE_MB * MB_TO_B_SCALE;
	std::cout << "DEALLOCATION: Deallocating " << size << " byes off heap" << std::endl;
	free(m_baseAddress);
}