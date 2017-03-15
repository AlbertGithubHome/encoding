#include "commondef.h"
#include "detection.h"
#include <fstream>

using namespace std;

// disable warning about strdup being deprecated.
#if _MSC_VER >= 1400	// VC++ 8.0
#pragma warning( disable : 4996 )
#endif

// define file size
#define MAX_FILE_CONTENT_SIZE	(4 *MB)

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
	if (NULL == szFileName)
		return e_detection_error_cannot_openfile;

	strncpy(m_szFileName, szFileName, MAX_FILE_NAME_LEN);
	m_szFileName[MAX_FILE_NAME_LEN - 1] = '\0';

	ifstream inputFile(m_szFileName, ios::binary);
	if (!inputFile)
	{
		return e_detection_error_cannot_openfile;
	}

	BYTE *pContentBuffer =  new BYTE[MAX_FILE_CONTENT_SIZE];
	if (NULL == pContentBuffer)
	{	
		inputFile.close();
		return e_detection_error_memory_lack;
	}
	memset(pContentBuffer, 0, MAX_FILE_CONTENT_SIZE);

	inputFile.read((char *)pContentBuffer, MAX_FILE_CONTENT_SIZE);
	int nReadCount =inputFile.gcount();


	int nHandleRet = e_detection_error_no_result;
	// ��ʼ������
	do 
	{
		if (MAX_FILE_CONTENT_SIZE == nReadCount)
		{
			nHandleRet = e_detection_error_file_toobig;
			break;
		}
		else if (nReadCount <= 1)
		{
			nHandleRet = e_encording_utf8_without_bom;
			break;
		}
		
		if (nReadCount >= 2)
		{
			if (pContentBuffer[0] == 0xFF && pContentBuffer[1] == 0xFE)
			{
				nHandleRet = e_encording_ucs2_little_endian;
				break;
			}
			else if (pContentBuffer[0] == 0xFE && pContentBuffer[1] == 0xFF)
			{
				nHandleRet = e_encording_ucs2_big_endian;
				break;
			}
		}
		
		if (nReadCount >= 3)
		{
			if (pContentBuffer[0] == 0xEF &&  pContentBuffer[1] == 0xBB && pContentBuffer[2] == 0xBF)
			{
				nHandleRet = e_encording_utf8;
				break;
			}
		}

		if (nReadCount >= 4)
		{
			if (pContentBuffer[0] == 0x0 && pContentBuffer[1] == 0x0 && pContentBuffer[2] == 0xFF && pContentBuffer[3] == 0xFE)
			{
				nHandleRet = e_encording_ucs4_little_endian;
				break;
			}

			if (pContentBuffer[0] == 0x0 && pContentBuffer[1] == 0x0 && pContentBuffer[2] == 0xFE && pContentBuffer[3] == 0xFF)
			{
				nHandleRet = e_encording_ucs4_big_endian;
				break;
			}
		}

		bool bIsASCII = true;	// Ĭ��ΪASCII��Ҳ�����ַ���С��128
		for (int nIndex = 0; nIndex < nReadCount; ++nIndex)
		{
			if (pContentBuffer[nIndex] <= ANSI_BYTE_END_VALUE)
				continue;
			
			bIsASCII = false;
			if (pContentBuffer[nIndex] >= UTF8_OTHER_BYTE_BEGIN_VALUE && pContentBuffer[nIndex] <= UTF8_OTHER_BYTE_END_VALUE)
			{
				nHandleRet = e_encording_ansi;
				break;
			}
			else
			{
				int nUft8WordSize = GetWordByteSize(pContentBuffer[nIndex]);
				if (nUft8WordSize <= 0)	// ����˴�˵���ļ������⣬��δ���ֹ�
				{
					nHandleRet = e_detection_error_cannot_detection;
					break;
				}

				for(int nHeadIndex = nIndex + 1; nHeadIndex <= nIndex + nUft8WordSize - 1; ++nHeadIndex)
				{
					if (pContentBuffer[nHeadIndex] >= UTF8_OTHER_BYTE_BEGIN_VALUE && pContentBuffer[nHeadIndex] <= UTF8_OTHER_BYTE_END_VALUE)
						continue;

					nHandleRet = e_encording_ansi;
					nIndex = nReadCount;	// Ϊ���������ѭ��
					break;
				}
				nIndex += (nUft8WordSize - 1);
			}
		}
	} while (false);

	// ǰ���߼���û�ҵ�˵����e_encording_utf8_without_bom
	if (e_detection_error_no_result == nHandleRet)
	{
		nHandleRet = e_encording_utf8_without_bom;
	}

	// �ͷ���Դ
	safe_delete_array(pContentBuffer);
	inputFile.close();

	return nHandleRet;
}

int CDetectionEncoding::GetWordByteSize(unsigned ucWordHead)
{
	if (ucWordHead <= UTF8_1BYTE_END_VALUE)				// 1�ֽ�
		return 1;
	else if (ucWordHead <= UTF8_OTHER_BYTE_END_VALUE)	// �����ֽ�
		return 0;
	else if (ucWordHead <= UTF8_2BYTE_END_VALUE)		// 2�ֽ�
		return 2;
	else if (ucWordHead <= UTF8_3BYTE_END_VALUE)		// 3�ֽ�
		return 3;
	else if (ucWordHead <= UTF8_4BYTE_END_VALUE)		// 4�ֽ�
		return 4;
	else if (ucWordHead <= UTF8_5BYTE_END_VALUE)		// 5�ֽ�
		return 5;
	else if (ucWordHead <= UTF8_6BYTE_END_VALUE)		// 6�ֽ�
		return 6;

	return 0;
}
