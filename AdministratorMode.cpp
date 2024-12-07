#include "AdministratorMode.h"
#include <iostream>
#include <random>
#include "Exception.h"

/*
Constructor for the AdministratorMode class
*/
AdministratorMode::AdministratorMode(Repository EventRepository)
{
	this->EventRepository = EventRepository;
}
/*
Function that adds an event to the repository
returns true if the event was added, false otherwise
*/
void AdministratorMode::addEvent(std::string title, std::string description, Date date, Time time, int numberOfPeople, std::string link)
{
	Event eventToAdd{ title, description, date, time, numberOfPeople, link };
	this->EventRepository.addEvent(eventToAdd);

	AddCommand* addCommand = new AddCommand(&this->EventRepository, eventToAdd);
	this->undoRedo.addOperation(addCommand);



}
/*
Function that deletes an event from the repository
returns true if the event was deleted, false otherwise
*/
void AdministratorMode::deleteEvent(std::string title, std::string link)
{
	Event eventToDelete{ title, "", {0,0}, {0,0}, 0, link };
	int index = this->EventRepository.findEvent(eventToDelete);
	eventToDelete = { this->EventRepository.getEvents()[index].getTitle(), this->EventRepository.getEvents()[index].getDescription(), this->EventRepository.getEvents()[index].getDate(), this->EventRepository.getEvents()[index].getTime(), this->EventRepository.getEvents()[index].getNumberOfPeople(), this->EventRepository.getEvents()[index].getLink() };

	this->EventRepository.deleteEvent(index);

	RemoveCommand* removeCommand = new RemoveCommand(&this->EventRepository, eventToDelete);
	this->undoRedo.addOperation(removeCommand);


}
/*
Function that updates an event from the repository
returns true if the event was updated, false otherwise
*/
void AdministratorMode::updateEvent(std::string title, std::string link, std::string new_title, std::string description, Date date, Time time, int numberOfPeople, std::string new_link)
{
	Event eventToUpdate{ title, "", {0,0}, {0,0}, 0, link };
	int index = this->EventRepository.findEvent(eventToUpdate);
	eventToUpdate = { this->EventRepository.getEvents()[index].getTitle(), this->EventRepository.getEvents()[index].getDescription(), this->EventRepository.getEvents()[index].getDate(), this->EventRepository.getEvents()[index].getTime(), this->EventRepository.getEvents()[index].getNumberOfPeople(), this->EventRepository.getEvents()[index].getLink() };
	Event newEvent{ new_title, description, date, time, numberOfPeople, new_link };
	this->EventRepository.updateEvent(index, newEvent);

	UpdateCommand* updateCommand = new UpdateCommand(&this->EventRepository, eventToUpdate, newEvent);
	this->undoRedo.addOperation(updateCommand);


}
/*
Function that returns the events from the repository

*/
std::vector<Event> AdministratorMode::getEvents()
{
	return this->EventRepository.getEvents();
}
/*
generates a random day and month
*/
Date generateRandomDate()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 30);
	int day = dis(gen);
	std::uniform_int_distribution<> dis2(1, 12);
	int month = dis2(gen);
	Date date{ day, month };
	return date;
}
/*
generates a random hour and minute

*/
Time generateRandomTime()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 23);
	int hour = dis(gen);
	std::uniform_int_distribution<> dis2(0, 59);
	int minute = dis2(gen);
	Time time{ hour, minute };
	return time;
}
/*
Function that adds 10 events to the repository
well knows sites
*/
void AdministratorMode::tenEvents()
{
	Date date1 = generateRandomDate();
	Time time1 = generateRandomTime();
	this->addEvent("Reel Watching", "Watching reels on youtube", date1, time1, 5124, "https://www.youtube.com/");

	Date date2 = generateRandomDate();
	Time time2 = generateRandomTime();
	this->addEvent("Instagram scrolling", "Scrolling through instagram", date2, time2, 3123, "https://www.instagram.com/");

	Date date3 = generateRandomDate();
	Time time3 = generateRandomTime();
	this->addEvent("Facebook scrolling", "Scrolling through facebook", date3, time3, 1234, "https://www.facebook.com/");

	Date date4 = generateRandomDate();
	Time time4 = generateRandomTime();
	this->addEvent("Twitter scrolling", "Scrolling through twitter", date4, time4, 2345, "https://www.twitter.com/");

	Date date5 = generateRandomDate();
	Time time5 = generateRandomTime();
	this->addEvent("TikTok scrolling", "Scrolling through tiktok", date5, time5, 3456, "https://www.tiktok.com/");

	Date date6 = generateRandomDate();
	Time time6 = generateRandomTime();
	this->addEvent("Reddit scrolling", "Scrolling through reddit", date6, time6, 4567, "https://www.reddit.com/");

	Date date7 = generateRandomDate();
	Time time7 = generateRandomTime();
	this->addEvent("LinkedIn scrolling", "Scrolling through linkedin", date7, time7, 5678, "https://www.linkedin.com/");

	Date date8 = generateRandomDate();
	Time time8 = generateRandomTime();
	this->addEvent("Snapchat scrolling", "Scrolling through snapchat", date8, time8, 6789, "https://www.snapchat.com/");

	Date date9 = generateRandomDate();
	Time time9 = generateRandomTime();
	this->addEvent("Pinterest scrolling", "Scrolling through pinterest", date9, time9, 7890, "https://www.pinterest.com/");

	Date date10 = generateRandomDate();
	Time time10 = generateRandomTime();
	this->addEvent("Tumblr scrolling", "Scrolling through tumblr", date10, time10, 8901, "https://www.tumblr.com/");

}

void AdministratorMode::copyRepoAdmin(std::vector<Event> events_to_copy)
{
	for (auto event : events_to_copy)
		this->EventRepository.updateEvent(this->EventRepository.findEvent(event), event);

}

void AdministratorMode::executeUndo()
{
	this->undoRedo.executeUndo();
}

void AdministratorMode::executeRedo()
{
	this->undoRedo.executeRedo();
}


