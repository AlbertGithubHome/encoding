# API Instructions
---

## moudles

### IDetectionEncoding

- GetEncoding
 
 - 功能：返回指定文件的编码格式，如果既是UTF8无BOM又是ANSI默认返回“UTF8无BOM”
 - 参数：szFileName表示输入的文件名
 - 返回值：返回文件编码，当返回值<0时参考E_DETECTION_ERROR查找错误信息，当返回值>=0参考E_ENCODING_TYPE查找文件编码