#ifndef __CONVERTOR_INTERFACE_H__
#define __CONVERTOR_INTERFACE_H__

#include "detection_interface.h"

interface IEncodingConverter
{
public:
	virtual int	ConvertEncoding(const char *szFileName, const E_ENCODING_TYPE eSrcEncoding, const E_ENCODING_TYPE eDestEncoding) = 0;
};

#endif // __CONVERTOR_INTERFACE_H__