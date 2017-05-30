#include "memoryblock.h"

CMemoryBlockMgr::CMemoryBlockMgr()
{

}

CMemoryBlockMgr::~CMemoryBlockMgr()
{

}

CMemoryBlockMgr& CMemoryBlockMgr::Singleton()
{
	static CMemoryBlockMgr objInstance;
	return objInstance;
}

CMemoryBlock<char> CMemoryBlockMgr::GetFileContentBlock()
{
	return mFileContentBlockObject;
}



