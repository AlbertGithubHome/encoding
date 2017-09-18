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
	// 标记一个word的起始字节范围与字节数的对应关系
	unsigned char m_utf8_word_bytes_checklist[utf8_word_bytes_checklist];

	unsigned char* m_file_content;
};

#endif // __DETECTION_H__