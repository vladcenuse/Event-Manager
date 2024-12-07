#pragma once

#include "Event.h"
#include <vector>


class Repository
{
private:
	std::vector<Event> events;
	std::string filename;

public:
	Repository(std::string filename, std::vector<Event> initialEvents = {});
	Repository() : filename{ "" } {}
	std::vector<Event> getEvents() const;
	void addEvent(Event eventToAdd);
	void deleteEvent(int index);
	void updateEvent(int index, Event newEvent);
	int findEvent(Event eventToFind);

	void deleteAllEvents();

private:
	void readFromFile();
	void writeToFile();


};