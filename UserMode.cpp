#include "UserMode.h"
#include <iostream>
#include "Exception.h"
#include "CSVEventList.h"
#include "HTMLEventList.h"
/*
* Constructor for the UserMode class
*/

UserMode::UserMode(Repository initialRepo, FileEventList* EventList)
{
	this->eventsRepo = initialRepo;
	this->EventList = EventList;
}
/*
* Function that returns the eventlist
*
*/
FileEventList* UserMode::GetWatchList()
{
	return this->EventList;
}
/*
* Function that adds an event to the watchlist
* returns true if the event was added, false otherwise
*/
void UserMode::AddEventToWatchList(Event event)
{
	std::vector<Event> events = this->EventList->getEvents();
	auto it = std::find(events.begin(), events.end(), event);
	if (it == events.end())
	{
		int index = this->eventsRepo.findEvent(event);
		Event e = event;
		e.setNumberOfPeople(e.getNumberOfPeople() + 1);
		this->eventsRepo.updateEvent(index, e);
		//this->watchList.push_back(e);
		this->EventList->addEvent(e);
	}
	else
	{
		throw Exception("Event already in watchlist");
	}

}


/*
* Function that removes an event from the watchlist
* returns true if the event was removed, false otherwise
*
*/
void UserMode::RemoveEventFromWatchList(std::string title, std::string link)
{
	for (auto& event : this->EventList->getEvents())
	{
		if (event.getTitle() == title && event.getLink() == link)
		{
			int index = this->eventsRepo.findEvent(event);
			Event e = event;
			e.setNumberOfPeople(e.getNumberOfPeople() - 1);
			this->eventsRepo.updateEvent(index, e);
			//this->watchList.erase(std::remove(this->watchList.begin(), this->watchList.end(), event), this->watchList.end());
			this->EventList->removeEvent(event);
			return;
		}
	}
	throw Exception("Event not in watchlist");

}
/*
* Function that returns all the events
*
*/
std::vector<Event> UserMode::GetAllEvents()
{
	return this->eventsRepo.getEvents();
}

/*
* Function that copies the events from the repository
*/
void UserMode::copyRepoUser(std::vector<Event> events_to_copy)
{
	this->eventsRepo.deleteAllEvents();
	for (auto& event : events_to_copy)
	{
		this->eventsRepo.addEvent(event);
	}
}
void UserMode::setEventList(std::string eventListType)
{
	if (eventListType == "CSV")
		this->EventList = new CSVEventList{ "watchlist.csv" };
	else if (eventListType == "HTML")
		this->EventList = new HTMLEventList{ "watchlist.html" };
}
void UserMode::saveWatchList()
{
	this->EventList->writeToFile();
}
void UserMode::openWatchList()
{
	this->EventList->displayWithApp();
}


/*
* Function that returns the events from a month sorted
* returns a vector of events
*
*/
std::vector <Event> UserMode::GetEventsFromAMonth(std::vector <Event> allTutorials, int month)
{
	if (month == 0) {
		std::vector<Event> emptyVector = allTutorials;
		for (auto& event_i : emptyVector) {
			for (auto& event_j : emptyVector) {
				if (event_i == event_j)
					continue;
				if (event_i.getDate().month > event_j.getDate().month) {
					std::swap(event_i, event_j);
				}
				else if (event_i.getDate().month == event_j.getDate().month) {
					if (event_i.getDate().day > event_j.getDate().day) {
						std::swap(event_i, event_j);
					}
				}
			}
		}
		std::reverse(emptyVector.begin(), emptyVector.end());
		return emptyVector;
	}
	std::vector<Event> eventsFromAMonth;
	for (auto& event : allTutorials) {
		if (event.getDate().month == month) {
			eventsFromAMonth.push_back(event);
		}
	}
	for (auto& event_i : eventsFromAMonth)
	{
		for (auto& event_j : eventsFromAMonth)
		{
			if (event_i.getDate().day > event_j.getDate().day) {
				std::swap(event_i, event_j);
			}
		}
	}
	std::reverse(eventsFromAMonth.begin(), eventsFromAMonth.end());
	return eventsFromAMonth;

}
