#include "HTMLEventList.h"
#include <Windows.h>

void HTMLEventList::writeEventToHtml(std::ostream& outputFile, const Event& event)
{
	outputFile << "<tr>\n"
		<< "<td>" << event.getTitle() << "</td>\n"


		<< "<td>" << event.getDescription() << "</td>\n";
	//<< "<td>" << event.getDate().day << '.' << event.getDate().month << ' ' << event.getTime().hour << ':' << event.getTime().minute << "</td>\n"
	if (event.getDate().day < 10)
		outputFile << "<td>" << "0" << event.getDate().day << '.';
	else
		outputFile << "<td>" << event.getDate().day << '.';
	if (event.getDate().month < 10)
		outputFile << "0" << event.getDate().month << ' ';
	else
		outputFile << event.getDate().month << ' ';
	if (event.getTime().hour < 10)
		outputFile << "0" << event.getTime().hour << ':';
	else
		outputFile << event.getTime().hour << ':';
	if (event.getTime().minute < 10)
		outputFile << "0" << event.getTime().minute << "</td>\n";
	else
		outputFile << event.getTime().minute << "</td>\n";
	outputFile << "<td>" << event.getNumberOfPeople() << "</td>\n"
		<< "<td>" << "<a href=\"" << event.getLink() << "\">" << "Link" << "</a>" << "</td>" << std::endl
		<< "</tr>\n";
}

void HTMLEventList::writeToFile()
{
	std::ofstream outputFile(this->filename);
	if (!outputFile.is_open())
		throw std::runtime_error("Could not open the file");
	outputFile << "<!DOCTYPE html>\n"
		<< "<html>\n"
		<< "	<head>\n"
		<< "		<title> Watchlist </title>\n"
		<< "	</head>\n"
		<< "<body>\n"
		<< "	<table border = ""1"">\n"
		<< "		<tr>\n"
		<< "			<td> Title </td>\n"
		<< "			<td> Description </td>\n"
		<< "			<td> Date and Time </td>\n"
		<< "			<td> Number of people going so far </td>\n"
		<< "			<td> Link </td>\n"
		<< "		</tr>" << std::endl;
	for (auto& event : this->allEvents)
		this->writeEventToHtml(outputFile, event);
	outputFile << "	</table>\n"
		<< "</body>\n"
		<< "</html>\n";
	outputFile.close();
}

void HTMLEventList::displayWithApp()
{
	char buffer[100];
	GetCurrentDirectoryA(100, buffer);
	std::string path = buffer;
	path += "\\" + this->filename;
	std::string command = "start \"\" \"" + path + "\"";
	system(command.c_str());
}