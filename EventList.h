#pragma once
#include <vector>
#include "Event.h"
class EventList
{
protected:
	std::vector <Event> allEvents;

public:
	EventList(std::vector <Event> events = {}) {}
	std::vector<Event> getEvents();
	void addEvent(Event event);
	void removeEvent(Event event);
	virtual ~EventList() {}
};
