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

	// �������UTF8��BOM����ANSIĬ�Ϸ��ء�UTF8��BOM��
	int	GetEncoding(const char *szFileName);

	// ��UTF8�ַ����ֽ��жϸõ��ʵ��ֽڸ���
	int GetWordByteSize(unsigned ucWordHead);

private:
	char m_szFileName[MAX_FILE_NAME_LEN];
};

#endif // __DETECTION_H__