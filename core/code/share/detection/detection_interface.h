#ifndef __DETECTION_INTERFACE_H__
#define __DETECTION_INTERFACE_H__

// ����ӿ�����
#define interface struct

interface IDetectionEncoding
{
public:
	virtual int	GetEncoding(const char *szFileName) = 0;
};


// ��ȡ����࣬����Ҫ�ͷ�
IDetectionEncoding*	CreateDetectionService();

// �жϼ���������Ƿ����
extern bool IsDetectionServiceValid(IDetectionEncoding* pDetectionService);


#endif // __DETECTION_INTERFACE_H__