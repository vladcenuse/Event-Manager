#include "EventList.h"

std::vector<Event> EventList::getEvents()
{
	return this->allEvents;
}

void EventList::addEvent(Event event)
{

	this->allEvents.push_back(event);
}

void EventList::removeEvent(Event event)
{
	auto it = std::find(this->allEvents.begin(), this->allEvents.end(), event);
	if (it != this->allEvents.end())
	{
		this->allEvents.erase(it);
	}
}

