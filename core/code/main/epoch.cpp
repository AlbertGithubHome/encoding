#include "commondef.h"
#include "detection_interface.h"
#include "memoryblock/memoryblock.h"
#include "converter.h"


int main(int argc, char **argv)
{

	printf("test Ok\n");


	IDetectionEncoding* pDetection = CreateDetectionService();
	if (!IsDetectionServiceValid(pDetection))
		return 0;

	int nResult = pDetection->GetEncoding("main.txt");
	printf("result = %d\n", nResult);


	CMemoryBlockMgr::Singleton().GetFileContentBlock();;//Initalize(100);

	B::Singleton();
	getchar();
}
