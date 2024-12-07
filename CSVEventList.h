#pragma once
#include "FileEventList.h"
class CSVEventList : public FileEventList
{
public:
	CSVEventList(const std::string& filename) : FileEventList{ filename } {};
	void writeToFile() override;
	void displayWithApp() override;
	~CSVEventList() {};
};
