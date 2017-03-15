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

	// 如果既是UTF8无BOM又是ANSI默认返回“UTF8无BOM”
	int	GetEncoding(const char *szFileName);

	// 由UTF8字符首字节判断该单词的字节个数
	int GetWordByteSize(unsigned ucWordHead);

private:
	char m_szFileName[MAX_FILE_NAME_LEN];
};

#endif // __DETECTION_H__