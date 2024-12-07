#pragma once
#include "AdministratorMode.h"
#include "UserMode.h"
class UI
{
private:
	AdministratorMode adminMode;
	UserMode userMode;

public:
	UI(AdministratorMode adminMode, UserMode userMode) : adminMode{ adminMode }, userMode{ userMode } {}
	//admin
	void printEvents();
	void addEventToList();
	void deleteEventFromList();
	void updateEventFromList();
	void adminModeRun();

	//user
	void printEventsUserUI();
	void GetEventsfromAMonthUI();
	void deleteEventFromUserListUI();
	void userModeRunUI();
	void saveWatchListUI();
	void openWatchListUI();

	//run
	void run();

};