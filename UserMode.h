#pragma once
#include "Repository.h"
#include "FileEventList.h"

class UserMode
{
private:
	Repository eventsRepo;
	FileEventList* EventList;
public:
	UserMode(Repository initialRepo, FileEventList* EventList = nullptr);
	std::vector <Event> GetEventsFromAMonth(std::vector <Event> allTutorials, int month);
	void AddEventToWatchList(Event event);
	void RemoveEventFromWatchList(std::string title, std::string link);
	std::vector <Event> GetAllEvents();
	FileEventList* GetWatchList();

	void copyRepoUser(std::vector <Event> events_to_copy);
	void setEventList(std::string eventListType);
	void saveWatchList();
	void openWatchList();
};