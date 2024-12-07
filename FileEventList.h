#pragma once
#include "EventList.h"
class FileEventList : public EventList
{
protected:
	std::string filename;
public:
	FileEventList(const std::string& filename) : filename{ filename } {};
	virtual void writeToFile() = 0;
	virtual void displayWithApp() = 0;
	virtual ~FileEventList() {};
};
