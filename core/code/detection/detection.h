#ifndef __DETECTION_H__
#define __DETECTION_H__

#include "detection_interface.h"

#define MAX_FILE_NAME_LEN	256

class CDetectionEncoding : public IDetectionEncoding
{
private:
	CDetectionEncoding();
	~CDetectionEncoding(){}
public:
	static CDetectionEncoding& GetSingleton();

	int	GetEncoding(const char *szFileName);

private:
	char m_szFileName[MAX_FILE_NAME_LEN];
};

#endif // __DETECTION_H__