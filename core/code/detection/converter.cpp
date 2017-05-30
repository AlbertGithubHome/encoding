#include "converter.h"
B::B()
{

}

B::~B()
{

}

B& B::Singleton()
{
	static B s;
	return s;
}

