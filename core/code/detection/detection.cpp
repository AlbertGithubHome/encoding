#include "commondef.h"
#include "detection.h"
#include <fstream>

using namespace std;

// disable warning about strdup being deprecated.
#if _MSC_VER >= 1400	// VC++ 8.0
#pragma warning( disable : 4996 )
#endif

// bom: byte order mark
unsigned char g_encoding_bom[e_encoding_type_max][6] = {
	{0x00},									// utf common format in linux or mac
	{0x00},									// common extend for ascii
	{0x03, 0xEF, 0xBB, 0xBF, 0x00},			// EF BB BF		UTF-8
	{0x02, 0xFE, 0xFF, 0x00},				// FF FE		UTF-16/UCS-2,big edian
	{0x02, 0xFF, 0xFE, 0x00},				// FE FF		UTF-16/UCS-2,little edian	
	{0x04, 0x00, 0x00, 0xFE, 0xFF, 0x00},	// 00 00 FF FE 	UTF-32/UCS-4,big edian
	{0x04, 0x00, 0x00, 0xFF, 0xFE, 0x00},	// 00 00 FE FF	UTF-32/UCS-4,little edian
};


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

void zencoding_detection::release_data()
{
	safe_delete_array(m_file_content);
}

bool zencoding_detection::allocate_space()
{
	m_file_content =  new unsigned char[MAX_FILE_CONTENT_SIZE + 1];
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
	int nReadCount = inputFile.gcount();
	inputFile.close();
	m_file_content[nReadCount] = '\0';

	if (MAX_FILE_CONTENT_SIZE == nReadCount)
		return e_detection_error_file_toobig;

	// check encoding with bom
	for (int encoding_type = e_encoding_utf8; encoding_type < e_encoding_type_max; ++encoding_type)
	{
		int n =  strlen((char*)g_encoding_bom[encoding_type]);
		if (!strncmp((char*)m_file_content, (char*)g_encoding_bom[encoding_type] + 1, g_encoding_bom[encoding_type][0]))
			return encoding_type;
	}

	// if the word is utf8 word that is not two bytes word, the variable will be auto-increment;
	int utf8_but_not_two_bytes_word_count = 0; 
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

			utf8_but_not_two_bytes_word_count += (utf8_word_size != 2) ? 1 : 0;
			for(int word_bytes_index = content_index + 1; word_bytes_index <= content_index + utf8_word_size - 1; ++word_bytes_index)
			{
				if (m_file_content[word_bytes_index] >= UTF8_OTHER_BYTE_BEGIN_VALUE && m_file_content[word_bytes_index] <= UTF8_OTHER_BYTE_END_VALUE)
					continue;

				return e_encoding_ansi;
			}
			content_index += (utf8_word_size - 1);
		}
	}

	// if all utf8 words have two bytes, it is ansi encoding in all probability.
	if (!utf8_but_not_two_bytes_word_count)
		return e_encoding_ansi;

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





