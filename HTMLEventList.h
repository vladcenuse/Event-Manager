#pragma once
#include <iostream>
#include <fstream>
#include "FileEventList.h"
class HTMLEventList : public FileEventList
{
private:
	void writeEventToHtml(std::ostream& outputFile, const Event& event);
public:
	HTMLEventList(const std::string& filename) : FileEventList{ filename } {};
	void writeToFile() override;
	void displayWithApp() override;
	~HTMLEventList() {};
};
