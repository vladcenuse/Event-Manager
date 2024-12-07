#include "Event.h"
#include <string>
#include <vector>
#include <iostream>

/*
Constructor for the Event class

*/
Event::Event(std::string title, std::string description, Date date, Time time, int numberOfPeople, std::string link)
{
	this->title = title;
	this->description = description;
	this->date = date;
	this->time = time;
	this->numberOfPeople = numberOfPeople;
	this->link = link;
}
/*
return the title of the event

*/
std::string Event::getTitle() const
{
	return this->title;
}
/*
return the description of the event
*/
std::string Event::getDescription() const
{
	return this->description;
}
/*
return the date of the event

*/
Date Event::getDate() const
{
	return this->date;
}
/*
returns  the time of the event


*/
Time Event::getTime() const
{
	return this->time;
}
/*
returns the number of people that are going to the event
*/
int Event::getNumberOfPeople() const
{
	return this->numberOfPeople;
}
/*
returns the link of the event

*/
std::string Event::getLink() const
{
	return this->link;
}
/*
sets the title of the event

*/
void Event::setTitle(std::string new_title)
{
	this->title = new_title;
}
/*
sets the description of the event


*/
void Event::setDescription(std::string new_description)
{
	this->description = new_description;
}
/*
sets the date of the event



*/
void Event::setDate(Date new_date)
{
	this->date = new_date;
}
/*
sets the time of the event


*/
void Event::setTime(Time new_time)
{
	this->time = new_time;
}
/*
sets the number of people that are going to the event


*/
void Event::setNumberOfPeople(int new_numberOfPeople)
{
	this->numberOfPeople = new_numberOfPeople;
}
/*
sets the link of the event
*/
void Event::setLink(std::string new_link)
{
	this->link = new_link;
}
/*
overloading the == operator
returns true if the events are equal, false otherwise

*/

bool Event::operator==(const Event& event_to_compare)
{
	return this->title == event_to_compare.title && this->link == event_to_compare.link;
}


/*
overloading the = operator
returns an event that is a copy of the one given as a parameter
*/
void Event::operator=(const Event& event_to_copy)
{
	this->title = event_to_copy.title;
	this->description = event_to_copy.description;
	this->date = event_to_copy.date;
	this->time = event_to_copy.time;
	this->numberOfPeople = event_to_copy.numberOfPeople;
	this->link = event_to_copy.link;
}
/*
* Overloading the >> operator
* Reads an event from the input stream
*/
std::istream& operator>>(std::istream& input, Event& event_to_read) {
	std::string lineRead;
	getline(input, lineRead);
	std::vector<std::string> tokens = splitString(lineRead, ',');
	if (tokens.size() != 6)
	{
		return input;
	}
	event_to_read.title = tokens[0];
	event_to_read.description = tokens[1];
	std::vector<std::string> dateTokens = splitString(tokens[2], ':');
	if (dateTokens.size() != 2)
	{
		return input;
	}
	event_to_read.date = Date{ std::stoi(dateTokens[0]), std::stoi(dateTokens[1]) };
	std::vector<std::string> timeTokens = splitString(tokens[3], ':');

	if (timeTokens.size() != 2)
	{
		return input;
	}
	event_to_read.time = Time{ std::stoi(timeTokens[0]), std::stoi(timeTokens[1]) };
	event_to_read.numberOfPeople = std::stoi(tokens[4]);
	event_to_read.link = tokens[5];
	return input;
}
/*
* Overloading the << operator
* Writes an event to the output stream
*/
std::ostream& operator<<(std::ostream& output, const Event& event_to_write) {
	std::string title_to_output = event_to_write.title;
	std::string description_to_output = event_to_write.description;
	std::string date_to_output = std::to_string(event_to_write.date.day) + ":" + std::to_string(event_to_write.date.month);
	std::string time_to_output = std::to_string(event_to_write.time.hour) + ":" + std::to_string(event_to_write.time.minute);
	std::string numberOfPeople_to_output = std::to_string(event_to_write.numberOfPeople);
	std::string link_to_output = event_to_write.link;
	std::string comma = ",";
	output << title_to_output << comma << description_to_output << comma << date_to_output << comma << time_to_output << comma << numberOfPeople_to_output << comma << link_to_output;
	return output;

}