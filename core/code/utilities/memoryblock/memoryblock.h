#ifndef __MEMORY_BLOCK_H__
#define __MEMORY_BLOCK_H__

#include "memory_interface.h"

class CMemoryBlockMgr //: public IMemoryBlockMgr
{
private:
	CMemoryBlockMgr();
	~CMemoryBlockMgr();

public:
	static CMemoryBlockMgr& Singleton();

	CMemoryBlock<char> GetFileContentBlock();

private:
	CMemoryBlock<char> mFileContentBlockObject;
};

// define g_MemBlockMgr
#define g_MemBlockMgr CMemoryBlockMgr::Singleton()
#endif // __MEMORY_BLOCK_H__