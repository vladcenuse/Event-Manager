
#include <iostream>
#include <crtdbg.h>
#include "UI.h"
#include "Exception.h"
#include "CSVEventList.h"
#include "HTMLEventList.h"
#include "Tema89.h"
#include <QtWidgets/QApplication>
#include "GUI.h"


int main(int argc, char* argv[])
{
	//an event is uniquely identified by its title and its link
	//taskkill /F /IM "Tema 4-5.exe" daca pusca
	{
		try {

			Repository repository{ "Event.txt" };
			FileEventList* EventList = nullptr;

			AdministratorMode adminMode{ repository };
			UserMode userMode{ repository,EventList };

			GUI gui{ adminMode,userMode};
			gui.startScreen();
		}
		catch (Exception& exception)
		{
			std::cout << exception.what();
		}

	}
	return 0;
}
