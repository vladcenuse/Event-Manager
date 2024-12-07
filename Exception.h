#pragma once
#include <exception>
#include <string>

class Exception : public std::exception
{
private:
	std::string message;

public:
	Exception(const std::string& messageToThrow);
	virtual const char* what();

};
