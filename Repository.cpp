#include "Repository.h"
#include <fstream>
#include <algorithm>
#include "Exception.h"	
/*
Constructor for the Repository class
*/
Repository::Repository(std::string filename, std::vector<Event> initialEvents) : events{ initialEvents }, filename{ filename }
{
	this->readFromFile();
}
/*
Function that returns the events from the repository
*/
std::vector<Event> Repository::getEvents() const
{
	return this->events;
}
/*
Function that adds an event to the repository
returns true if the event was added, false otherwise
*/
void Repository::addEvent(Event eventToAdd)
{
	auto iterator = std::find(this->events.begin(), this->events.end(), eventToAdd);
	if (iterator != this->events.end())
		throw Exception("The event already exists!");

	this->events.push_back(eventToAdd);
	this->writeToFile();

}
/*
Function that deletes an event from the repository
returns true if the event was deleted, false otherwise

*/
void Repository::deleteEvent(int index)
{
	if (index < 0 || index >= this->events.size())
		throw Exception("The event does not exist!");

	this->events.erase(this->events.begin() + index);
	this->writeToFile();
}
/*

Function that updates an event from the repository
returns true if the event was updated, false otherwise


*/

void Repository::updateEvent(int index, Event newEvent)
{
	if (index < 0 || index >= this->events.size())
		throw Exception("The event does not exist!");
	this->events[index] = newEvent;
	this->writeToFile();
}
/*
Function that finds an event in the repository
*/
int Repository::findEvent(Event eventToFind)
{
	auto iterator = std::find(this->events.begin(), this->events.end(), eventToFind);
	if (iterator == this->events.end())
		return -1;
	return std::distance(this->events.begin(), iterator);
}

void Repository::deleteAllEvents()
{
	this->events.clear(); // clears the vector
}

void Repository::readFromFile()
{
	std::ifstream file(this->filename);
	if (!file.is_open())
		throw Exception("The file could not be opened!");
	Event event;
	while (file >> event)
	{
		this->addEvent(event);
	}
	file.close();

}

void Repository::writeToFile()
{
	std::ofstream file(this->filename);
	if (!file.is_open())
		throw Exception("The file could not be opened!");
	for (auto event : this->events)
	{
		file << event << '\n';
	}
	file.close();
}




