#include "CSVEventList.h"
#include <fstream>
#include <iostream>
#include <Windows.h>
#include "Exception.h"
#include <shellapi.h>

void CSVEventList::writeToFile()
{
	std::ofstream outputFile{ this->filename };
	if (!outputFile.is_open())
		throw Exception{ "The file could not be opened!" };
	for (auto& event : this->allEvents)
	{
		outputFile << event << "\n";
	}
	outputFile.close();
}

void CSVEventList::displayWithApp()
{
	ShellExecuteA(NULL, "open", "C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE", this->filename.c_str(), NULL, SW_MAXIMIZE);
}