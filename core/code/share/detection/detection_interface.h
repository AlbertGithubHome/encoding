#ifndef __DETECTION_INTERFACE_H__
#define __DETECTION_INTERFACE_H__

// define interface type
#define interface struct

// define encording type
enum E_ENCODING_TYPE
{
	e_encording_utf8_without_bom = 0,
	e_encording_ansi = 1,
	e_encording_utf8 = 2,				// EF BB BF		UTF-8
	e_encording_ucs2_big_endian = 3,	// FF FE		UTF-16/UCS-2,big edian
	e_encording_ucs2_little_endian = 4,	// FE FF		UTF-16/UCS-2,little edian	
	e_encording_ucs4_big_endian = 5,	// 00 00 FF FE 	UTF-32/UCS-4,big edian
	e_encording_ucs4_little_endian = 6,	// 00 00 FE FF	UTF-32/UCS-4,little edian
};

// define detectiong error type
enum E_DETECTION_ERROR
{
	e_detection_error_cannot_detection = -1,
	e_detection_error_cannot_openfile = -2,
	e_detection_error_file_toobig = -3,
	e_detection_error_memory_lack = -4,
	e_detection_error_no_result = -100,
};

interface IDetectionEncoding
{
public:
	virtual int	GetEncoding(const char *szFileName) = 0;
};


// 获取检测类，不需要释放
IDetectionEncoding*	CreateDetectionService();

// 判断检测编码服务是否可用
extern bool IsDetectionServiceValid(IDetectionEncoding* pDetectionService);


#endif // __DETECTION_INTERFACE_H__