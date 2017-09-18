#include "commondef.h"
#include "detection_interface.h"
#include "memoryblock/memoryblock.h"
#include "converter.h"


int main(int argc, char **argv)
{

	printf("test Ok\n");

	CMemoryBlockMgr::Singleton().GetFileContentBlock();;//Initalize(100);

	B::Singleton();


	detection_infterface* detection_hander = create_detection_handler();
	if (!is_valid_detection_handler(detection_hander))
		return 0;

	int result = detection_hander->get_encoding("main.txt");
	printf("result = %d\n", result);
	
	getchar();
}
