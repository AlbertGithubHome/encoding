#include "commondef.h"
#include "detection.h"

IDetectionEncoding *CreateDetectionService()
{
	CDetectionEncoding& sDetection = CDetectionEncoding::GetSingleton();
	return &sDetection;
}

bool IsDetectionServiceValid(IDetectionEncoding* pDetectionService)
{
	return (NULL != pDetectionService);
}

CDetectionEncoding::CDetectionEncoding()
{
	memset(m_szFileName, 0, sizeof(m_szFileName));
}

CDetectionEncoding& CDetectionEncoding::GetSingleton()
{
	static CDetectionEncoding sDetection;
	return sDetection;
}

int CDetectionEncoding::GetEncoding(const char *szFileName)
{
	return 0;
}
