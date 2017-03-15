#ifndef __DETECTION_INTERFACE_H__
#define __DETECTION_INTERFACE_H__

// 定义接口类型
#define interface struct

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