#include "commondef.h"
#include "detection.h"
#include <fstream>

using namespace std;

// disable warning about strdup being deprecated.
#if _MSC_VER >= 1400	// VC++ 8.0
#pragma warning( disable : 4996 )
#endif

detection_infterface* create_detection_handler()
{
	zencoding_detection& ref_instance = zencoding_detection::get_instance();
	return ref_instance.is_valid_obj() ? &ref_instance : NULL;
}

bool is_valid_detection_handler(detection_infterface* detection_handler)
{
	return (NULL != detection_handler);
}

void zencoding_detection::init_data()
{
	// init word head <==> word bytes
	memset(m_utf8_word_bytes_checklist, 0, sizeof(m_utf8_word_bytes_checklist));
	for (int index = 0; index < utf8_word_bytes_checklist; ++index)
	{
		if (index <= UTF8_1BYTE_END_VALUE)				// 1字节
		{
			m_utf8_word_bytes_checklist[index] = 1;
		}
		else if (index <= UTF8_OTHER_BYTE_END_VALUE)	// 非首字节
		{
			m_utf8_word_bytes_checklist[index] = 0;
		}
		else if (index <= UTF8_2BYTE_END_VALUE)			// 2字节
		{
			m_utf8_word_bytes_checklist[index] = 2;
		}
		else if (index <= UTF8_3BYTE_END_VALUE)			// 3字节
		{
			m_utf8_word_bytes_checklist[index] = 3;
		}
		else if (index <= UTF8_4BYTE_END_VALUE)			// 4字节
		{
			m_utf8_word_bytes_checklist[index] = 4;
		}
		else if (index <= UTF8_5BYTE_END_VALUE)			// 5字节
		{
			m_utf8_word_bytes_checklist[index] = 5;
		}
		else if (index <= UTF8_6BYTE_END_VALUE)			// 6字节
		{
			m_utf8_word_bytes_checklist[index] = 6;
		}
	}

	// 初始化变量
	m_file_content = NULL;
}

bool zencoding_detection::allocate_space()
{
	m_file_content =  new unsigned char[MAX_FILE_CONTENT_SIZE];
	if (!m_file_content)
		printf("allocate memory space failed!\n");

	return m_file_content != NULL;
}

zencoding_detection& zencoding_detection::get_instance()
{
	static zencoding_detection instance_obj;
	if (!instance_obj.m_is_init)
	{
		instance_obj.init_data();
		instance_obj.allocate_space();
		instance_obj.m_is_init = 1;
	}
	return instance_obj;
}

int zencoding_detection::get_encoding(const char *file_name)
{
	if (NULL == file_name)
		return e_detection_error_cannot_openfile;

	ifstream inputFile(file_name, ios::binary);
	if (!inputFile)
		return e_detection_error_cannot_openfile;

	inputFile.read((char *)m_file_content, MAX_FILE_CONTENT_SIZE);
	int nReadCount =inputFile.gcount();
	inputFile.close();

	if (MAX_FILE_CONTENT_SIZE == nReadCount)
		return e_detection_error_file_toobig;

	if (nReadCount <= 1)
		return e_encoding_utf8_without_bom;

	if (nReadCount >= 2)
	{
		if (m_file_content[0] == 0xFF && m_file_content[1] == 0xFE)
			return e_encoding_ucs2_little_endian;
		else if (m_file_content[0] == 0xFE && m_file_content[1] == 0xFF)
			return e_encoding_ucs2_big_endian;
	}

	if (nReadCount >= 3 && (m_file_content[0] == 0xEF &&  m_file_content[1] == 0xBB && m_file_content[2] == 0xBF))
		return e_encoding_utf8;


	if (nReadCount >= 4)
	{
		if (m_file_content[0] == 0x0 && m_file_content[1] == 0x0 && m_file_content[2] == 0xFF && m_file_content[3] == 0xFE)
			return e_encoding_ucs4_little_endian;

		if (m_file_content[0] == 0x0 && m_file_content[1] == 0x0 && m_file_content[2] == 0xFE && m_file_content[3] == 0xFF)
			return e_encoding_ucs4_big_endian;
	}

	for (int content_index = 0; content_index < nReadCount; ++content_index)
	{
		if (m_file_content[content_index] <= ASCII_BYTE_END_VALUE)
			continue;

		if (m_file_content[content_index] >= UTF8_OTHER_BYTE_BEGIN_VALUE && m_file_content[content_index] <= UTF8_OTHER_BYTE_END_VALUE)
			return e_encoding_ansi;
		else
		{
			int utf8_word_size = get_utf8_word_bytes_size_by_head(m_file_content[content_index]);
			if (utf8_word_size <= 0)	// 进入此处说明文件有问题，不是正常的文本文件，至今还未出现过
				return e_detection_error_cannot_detection;

			for(int word_bytes_index = content_index + 1; word_bytes_index <= content_index + utf8_word_size - 1; ++word_bytes_index)
			{
				if (m_file_content[word_bytes_index] >= UTF8_OTHER_BYTE_BEGIN_VALUE && m_file_content[word_bytes_index] <= UTF8_OTHER_BYTE_END_VALUE)
					continue;

				return e_encoding_ansi;
			}
			content_index += (utf8_word_size - 1);
		}
	}

	// 前面逻辑都没找到说明是e_encoding_utf8_without_bom
	return e_encoding_utf8_without_bom;
}

int zencoding_detection::get_utf8_word_bytes_size_by_head(unsigned char word_head)
{
	return (int)m_utf8_word_bytes_checklist[word_head];
}

bool zencoding_detection::is_valid_obj()
{
	return !!m_file_content;
}



