#ifndef __DETECTION_H__
#define __DETECTION_H__
#include "detection_interface.h"

class zencoding_detection : public detection_infterface
{
private:
	zencoding_detection() { m_is_init = 0; }
	~zencoding_detection() { release_data(); }

	void init_data();

	bool allocate_space();

	void release_data();
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