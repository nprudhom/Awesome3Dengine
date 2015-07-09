#include "stdafx.h"
#include "MemoryManager.h"

using namespace std;

using namespace Yes;

inline void* operator new(size_t Size, const char* File, int Line)
{
	return CMemoryManager::Instance().Allocate(Size, File, Line, false);
}

inline void* operator new[](size_t Size, const char* File, int Line)
{
	return CMemoryManager::Instance().Allocate(Size, File, Line, true);
}

#define new new(__FILE__, __LINE__)

inline void operator delete(void* Ptr)
{
	return CMemoryManager::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr)
{
	return CMemoryManager::Instance().Free(Ptr, true);
}

#define delete CMemoryManager::Instance().NextDelete(__FILE__, __LINE__), delete

inline void operator delete(void* Ptr, const char* File, int Line)
{
	CMemoryManager::Instance().NextDelete(File, Line);
	CMemoryManager::Instance().Free(Ptr, false);
}

inline void operator delete[](void* Ptr, const char* File, int Line)
{
	CMemoryManager::Instance().NextDelete(File, Line);
	CMemoryManager::Instance().Free(Ptr, true);
}