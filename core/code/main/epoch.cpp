#include "commondef.h"
#include "detection_interface.h"

int main(int argc, char **argv)
{

	printf("test Ok\n");


	IDetectionEncoding* pDetection = CreateDetectionService();
	if (!IsDetectionServiceValid(pDetection))
		return 0;

	int nResult = pDetection->GetEncoding("");
	printf("result = %d\n", nResult);


	getchar();
}
