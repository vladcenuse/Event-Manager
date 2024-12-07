#pragma once
#include "Repository.h"
#include "UndoRedo.h"

class AdministratorMode
{
private:
	Repository EventRepository;
	UndoRedo undoRedo;

public:
	AdministratorMode(Repository EventRepository);
	void addEvent(std::string title, std::string description, Date date, Time time, int numberOfPeople, std::string link);
	void deleteEvent(std::string title, std::string link);
	void updateEvent(std::string title, std::string link, std::string new_title, std::string description, Date date, Time time, int numberOfPeople, std::string new_link);

	std::vector<Event> getEvents();
	void tenEvents();

	void copyRepoAdmin(std::vector<Event> events_to_copy);

	void executeUndo();
	void executeRedo();


};