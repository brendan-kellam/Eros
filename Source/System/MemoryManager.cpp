
#include "System/MemoryManager.h"



void CMemoryManager::StartUp()
{
	using namespace std;
	using namespace std::chrono;

	int  size = MEMORY_ALLOCATION_SIZE_MB * MB_TO_B_SCALE;
	std::cout << "ALLOCATION: Allocating " << size << " bytes onto heap" << std::endl;
	

	auto t1 = EROS_TIME_NOW;

	// Allocate static-sized memory block on heap
	m_point = malloc(MEMORY_ALLOCATION_SIZE_MB * MB_TO_B_SCALE);
	
	// Assert memory was correctly initialized
	EROS_TRAP(m_point != nullptr);
	
	auto t2 = EROS_TIME_NOW;

	auto duration = EROS_DURATION_MILLI(t1, t2);
	
	cout << "Heap allocation time: " << duration << " milliseconds" << endl;

}

void CMemoryManager::ShutDown()
{
	int  size = MEMORY_ALLOCATION_SIZE_MB * MB_TO_B_SCALE;
	std::cout << "DEALLOCATION: Deallocating " << size << " byes off heap" << std::endl;
	free(m_point);
}