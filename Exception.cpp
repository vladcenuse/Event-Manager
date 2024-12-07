#include "Exception.h"

Exception::Exception(const std::string& messageToThrow) : message{ messageToThrow }
{
}

const char* Exception::what()
{
	return this->message.c_str();
}