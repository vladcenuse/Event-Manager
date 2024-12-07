#include "UI.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include "Exception.h"
#include "Validators.h"

void printAdminMenu() {
	std::cout << "You are in administrator mode!\n";
	std::cout << "1. Add event\n";
	std::cout << "2. Delete event\n";
	std::cout << "3. Update event\n";
	std::cout << "4. Print all events\n";
	std::cout << "0. Return\n";
}


void UI::printEvents() {
	std::cout << "The events are:\n";
	std::vector<Event> events = this->adminMode.getEvents();
	int index = 1;
	for (auto& currentEvent : events)
	{
		std::cout << "#" << index << ' ' << currentEvent.getTitle() << " " << '\n';
		std::cout << currentEvent.getDescription() << '\n';
		std::cout << "Date and Time: ";
		if (currentEvent.getDate().day < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().day << '.';
		if (currentEvent.getDate().month < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().month << ' ';
		if (currentEvent.getTime().hour < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().hour << ':';
		if (currentEvent.getTime().minute < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().minute << '\n';
		std::cout << "Number of people going so far: " << currentEvent.getNumberOfPeople() << '\n';
		std::cout << "Link: " << currentEvent.getLink() << '\n';
		std::cout << '\n';
		index++;
	}
}

void validateDate(Date date) {
	if (date.day < 1 || date.day > 30 || date.month < 1 || date.month > 12)
		throw Exception("Invalid date!");
}

void validateTime(Time time) {
	if (time.hour < 0 || time.hour > 23 || time.minute < 0 || time.minute > 59)
		throw Exception("Invalid time!");
}
void validateMonth(int month) {
	if (month < 0 || month > 12)
		throw Exception("Invalid month!");
}
void validateNumberOfPeople(int numberOfPeople) {
	if (numberOfPeople < 0)
		throw Exception("Invalid number of people!");
}

void UI::addEventToList() {

	std::string title = "", description = "", link = "";
	Date date;
	Time time;
	int numberOfPeople;
	bool added = false;
	try {
		std::cout << "Title: ";
		//std::cin.ignore();
		std::getline(std::cin, title);
		std::cout << "Description: ";
		//std::cin.ignore();
		std::getline(std::cin, description);
		std::cout << "Date (day month): ";
		std::cin >> date.day >> date.month;
		//validateDate(date);
		Validators::validateDate(date);
		std::cout << "Time (hour minute): ";
		std::cin >> time.hour >> time.minute;
		//validateTime(time);
		Validators::validateTime(time);
		std::cout << "Number of people: ";
		std::cin >> numberOfPeople;
		//validateNumberOfPeople(numberOfPeople);
		Validators::validateNumberOfPeople(numberOfPeople);
		std::cout << "Link: ";
		std::cin.ignore();
		std::getline(std::cin, link);
		this->adminMode.addEvent(title, description, date, time, numberOfPeople, link);
		std::cout << "Event added successfully!\n";
	}
	catch (Exception& e) {
		std::cout << e.what() << '\n';
	}

}

void UI::deleteEventFromList() {
	std::string title, link;

	std::cout << "Title: ";
	//std::cin.ignore();
	std::getline(std::cin, title);
	std::cout << "Link: ";
	//std::cin.ignore();
	std::getline(std::cin, link);
	try {
		this->adminMode.deleteEvent(title, link);
		std::cout << "Event deleted successfully!\n";
	}
	catch (Exception& e) {
		std::cout << e.what() << '\n';
	}

}

void UI::updateEventFromList() {
	std::string title, link, new_title, description, new_link;
	Date date, new_date;
	Time time, new_time;
	int numberOfPeople, new_numberOfPeople;
	try {

		std::cout << "Title: ";
		//std::cin.ignore();
		std::getline(std::cin, title);
		std::cout << "Link: ";
		//std::cin.ignore();
		std::getline(std::cin, link);
		std::cout << "New title: ";
		//std::cin.ignore();
		std::getline(std::cin, new_title);
		std::cout << "Description: ";
		//std::cin.ignore();
		std::getline(std::cin, description);
		std::cout << "Date (day month): ";
		std::cin >> new_date.day >> new_date.month;
		//validateDate(new_date);
		Validators::validateDate(new_date);
		std::cout << "Time (hour minute): ";
		std::cin >> new_time.hour >> new_time.minute;
		//validateTime(new_time);
		Validators::validateTime(new_time);
		std::cout << "Number of people: ";
		std::cin >> new_numberOfPeople;
		//validateNumberOfPeople(new_numberOfPeople);
		Validators::validateNumberOfPeople(new_numberOfPeople);
		std::cout << "New link: ";
		std::cin.ignore();
		std::getline(std::cin, new_link);
		this->adminMode.updateEvent(title, link, new_title, description, new_date, new_time, new_numberOfPeople, new_link);
	}
	catch (Exception& e) {
		std::cout << e.what() << '\n';
	}

}

void UI::adminModeRun() {
	bool running = true;
	while (running) {
		printAdminMenu();
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cin.ignore();
		switch (command) {
		case 1:
			this->addEventToList();
			break;
		case 2:
			this->deleteEventFromList();
			break;
		case 3:
			this->updateEventFromList();
			break;
		case 4:
			this->printEvents();
			break;
		case 0:
			running = false;
			return;
		default:
			std::cout << "Invalid command!\n";
			break;
		}
	}
}

void UI::printEventsUserUI() {
	if (this->userMode.GetWatchList()->getEvents().size() == 0)
	{
		std::cout << "No events in watchlist!\n";
		return;
	}
	std::cout << "The events are:\n";
	std::vector<Event> events = this->userMode.GetWatchList()->getEvents();
	int index = 1;
	for (auto& currentEvent : events)
	{
		std::cout << "#" << index << ' ' << currentEvent.getTitle() << " " << '\n';
		std::cout << currentEvent.getDescription() << '\n';
		std::cout << "Date and Time: ";
		if (currentEvent.getDate().day < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().day << '.';
		if (currentEvent.getDate().month < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().month << ' ';
		if (currentEvent.getTime().hour < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().hour << ':';
		if (currentEvent.getTime().minute < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().minute << '\n';
		std::cout << "Number of people going so far: " << currentEvent.getNumberOfPeople() << '\n';
		std::cout << "Link: " << currentEvent.getLink() << '\n';
		std::cout << '\n';
		index++;
	}

}
void UI::GetEventsfromAMonthUI() {
	this->userMode.copyRepoUser(this->adminMode.getEvents());
	int month;
	std::string monthString;
	std::cout << "Enter month: ";
	std::getline(std::cin, monthString);
	if (std::strlen(monthString.c_str()) != NULL)
	{
		month = std::stoi(monthString);
		try
		{
			//validateMonth(month);
			Validators::validateMonth(month);
		}
		catch (Exception& e) {
			std::cout << e.what() << '\n';
		}

	}
	else
		month = 0;


	std::vector<Event> Monthlyevents = this->userMode.GetEventsFromAMonth(this->adminMode.getEvents(), month);
	int current_index = 0;
	while (true) {
		if (Monthlyevents.size() == 0)
		{
			std::cout << "No events in this month!\n";
			break;
		}
		if (current_index == Monthlyevents.size())
		{
			current_index = 0;
		}
		Event currentEvent = Monthlyevents[current_index];
		std::cout << "#" << current_index + 1 << " " << currentEvent.getTitle() << " " << '\n';
		std::cout << currentEvent.getDescription() << '\n';
		std::cout << "Date and Time: ";
		if (currentEvent.getDate().day < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().day << '.';
		if (currentEvent.getDate().month < 10)
			std::cout << "0";
		std::cout << currentEvent.getDate().month << ' ';
		if (currentEvent.getTime().hour < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().hour << ':';
		if (currentEvent.getTime().minute < 10)
			std::cout << "0";
		std::cout << currentEvent.getTime().minute << '\n';
		std::cout << "Number of people going so far: " << currentEvent.getNumberOfPeople() << '\n';
		std::cout << "Link: " << currentEvent.getLink() << '\n';
		std::cout << '\n';

		std::string command = "start " + currentEvent.getLink();
		system(command.c_str());


		std::string answer;
		std::cout << "Do you want to add this event to your watchlist? (yes/next): \n";
		std::cout << "Write exit to exit\n";

		while (true) {
			std::cout << "Enter command: ";
			std::cin >> answer;

			if (answer.compare("yes") == 0)
			{
				try
				{
					this->userMode.AddEventToWatchList(currentEvent);
				}
				catch (Exception& e)
				{
					std::cout << e.what() << '\n';
				}
				current_index++;
				this->adminMode.copyRepoAdmin(this->userMode.GetAllEvents());
				break;
			}
			else if (answer.compare("next") == 0)
			{
				current_index++;
				break;
			}
			else if (answer.compare("exit") == 0)
			{
				return;
			}
			else
			{
				std::cout << "Invalid command!\n";
			}

		}
		std::cout << '\n';
	}
}
void UI::deleteEventFromUserListUI() {
	std::string title, link;

	std::cout << "Title: ";
	//std::cin.ignore();
	std::getline(std::cin, title);
	std::cout << "Link: ";
	//std::cin.ignore();
	std::getline(std::cin, link);
	try {
		this->userMode.RemoveEventFromWatchList(title, link);
		std::cout << "Event deleted successfully!\n";
		this->adminMode.copyRepoAdmin(this->userMode.GetAllEvents());
	}
	catch (Exception& e) {
		std::cout << e.what() << '\n';
	}
}
void printUserMenu() {
	std::cout << "You are in user mode!\n";
	std::cout << "1. Get events from a month\n";
	std::cout << "2. Print eventlist\n";
	std::cout << "3. Delete event from eventlist\n";
	std::cout << "4. Save eventlist\n";
	std::cout << "5. Open eventlist\n";
	std::cout << "0. Return\n";

}
void UI::saveWatchListUI()
{

	this->userMode.saveWatchList();

}

void UI::openWatchListUI()
{
	this->userMode.openWatchList();
}

void UI::userModeRunUI() {
	bool running = true;
	while (running) {
		printUserMenu();
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cin.ignore();
		switch (command) {
		case 1:
			this->GetEventsfromAMonthUI();
			break;
		case 2:
			this->printEventsUserUI();
			break;
		case 3:
			this->deleteEventFromUserListUI();
			break;
		case 4:
			this->saveWatchListUI();
			break;
		case 5:
			this->openWatchListUI();
			break;
		case 0:
			running = false;
			return;
		default:
			std::cout << "Invalid command!\n";
			break;
		}
	}

}



void UI::run() {
	bool running = true;
	while (running) {
		std::cout << "1. Administrator mode\n";
		std::cout << "2. User mode\n";
		std::cout << "0. Exit\n";
		int command;
		std::cout << "Enter command: ";
		std::cin >> command;
		std::cin.ignore();
		switch (command) {
		case 1:
			this->adminModeRun();
			break;
		case 2:
			this->userModeRunUI();
			break;
		case 0:
			running = false;
			exit(0);
		default:
			std::cout << "Invalid command!\n";
			break;
		}
	}
}