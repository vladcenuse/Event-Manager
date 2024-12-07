#include "StringTokenizer.h"
#include <sstream>
/*
* Deletes spaces before and after the string
*/
std::string trimString(const std::string& str)
{
	std::string result(str);
	size_t first = result.find_first_not_of(' ');
	if (first != -1)
		result.erase(0, first);
	size_t last = result.find_last_not_of(' ');
	if (last != std::string::npos)
		result.erase(last + 1);
	return result;

}
/*
* Splits the string by the delimiter
* @param str - the string to be split
* @param delimiter - the delimiter
* @return a vector of strings
*/

std::vector<std::string> splitString(const std::string& str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, delimiter))
	{
		result.push_back(token);
	}
	return result;

}