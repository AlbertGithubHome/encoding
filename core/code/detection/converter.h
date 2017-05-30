#ifndef __CONVERTOR_H__
#define __CONVERTOR_H__


class B
{
private:
	B();
	~B();

public:
	static B& Singleton();
};

#endif // __CONVERTOR_H__