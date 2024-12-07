#pragma once
#include <qobject.h>
#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QListWidget>
#include "AdministratorMode.h"
#include "UserMode.h"

class GUI : public QObject
{
	Q_OBJECT
	private:
		AdministratorMode adminMode;
		UserMode userMode;
		int argumentCount;
		char** argumentVector;
	public:
		GUI(AdministratorMode initialadminMode, UserMode initialuserMode, int argumentCount = 0, char** argumentVector = nullptr);
		int startScreen();

		int printAdminMenu();
		int printUserMenu();


		int addEvent();
		int deleteEventfromAdmin();
		int updateEvent();
		int displayEvents();

		int getEventsFromAMonth();
		int removeEventFromEventList();
		int displayEventList();
		void detailsEvent(const Event& event, QLabel& label);
		int saveEventListtoFile();
		int openEventList();

		void displayError(const char* message);

		private slots:
		void AddAdminButtonClicked();
		void DeleteAdminButtonClicked();
		void UpdateAdminButtonClicked();

		void UserModeRunMode();
		void AdminModeRunMode();

		void UndoButtonClicked();
		void RedoButtonClicked();


};