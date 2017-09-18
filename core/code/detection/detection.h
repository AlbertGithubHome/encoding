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


class zencoding_detection : public detection_infterface
{
private:
	zencoding_detection() { m_is_init = 0; }
	~zencoding_detection() {}

	void init_data();

	bool allocate_space();
public:
	static zencoding_detection& get_instance();

	bool is_valid_obj();

	int get_encoding(const char *file_name);

	int get_utf8_word_bytes_size_by_head(unsigned char word_head);

private:
	unsigned char m_is_init;
	enum {utf8_word_bytes_checklist = 256};
	// ���һ��word����ʼ�ֽڷ�Χ���ֽ����Ķ�Ӧ��ϵ
	unsigned char m_utf8_word_bytes_checklist[utf8_word_bytes_checklist];

	unsigned char* m_file_content;
};

#endif // __DETECTION_H__