#include "Gui.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QDialog>
#include <QInputDialog>
#include <warning.h>
#include <qmessagebox.h>
#include <iostream>
#include <QGroupBox>
#include "Exception.h"
#include "Validators.h"
#include "EventListModel.h"
#include <Qshortcut>

GUI::GUI(AdministratorMode initialadminMode, UserMode initialuserMode, int argumentCount, char** argumentVector) : adminMode{ initialadminMode }, userMode{ initialuserMode }, argumentCount{ argumentCount }, argumentVector{ argumentVector }
{


}

int GUI::startScreen()
{
	QApplication application{ argumentCount, argumentVector };

	QWidget window{};
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1; font-size: 20px;");

	window.setWindowTitle("Events");

	QVBoxLayout* mainFrame = new QVBoxLayout{};
	QHBoxLayout* buttonFrame = new QHBoxLayout{};
	QLabel* titleLabel = new QLabel("Event Manager App");
	titleLabel->setAlignment(Qt::AlignCenter);
	titleLabel->setStyleSheet("font-size: 30px; font-weight: bold; margin-bottom: 20px; color: #ECF0F1;");

	QPushButton* adminButton = new QPushButton("Administrator Mode");
	QPushButton* userButton = new QPushButton("User Mode");

	adminButton->setStyleSheet("background-color: #34495E; color: #ECF0F1;");
	userButton->setStyleSheet("background-color: #34495E; color: #ECF0F1;");
	
	connect(adminButton, &QPushButton::clicked, this, &GUI::printAdminMenu);
	connect(userButton, &QPushButton::clicked, this, &GUI::printUserMenu);


	buttonFrame->addWidget(adminButton);
	buttonFrame->addWidget(userButton);

	mainFrame->addWidget(titleLabel);
	mainFrame->addLayout(buttonFrame);

	window.setLayout(mainFrame);
	window.resize(500, 250);
	window.show();

	return application.exec();
}

int GUI::printAdminMenu()
{
	QDialog* adminMenu = new QDialog{};
	QWidget window{adminMenu};
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("Admin mode");
	title.setAlignment(Qt::AlignCenter);
	title.setStyleSheet("color: #ECF0F1;");

	QListWidgetItem* element1 = new QListWidgetItem("1. Add a new event", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Delete a event", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Update a event", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Display all events", &list);

	QPushButton* undoButton = new QPushButton("Undo");
	QPushButton* redoButton = new QPushButton("Redo");


	layout.addWidget(&title);
	layout.addWidget(&list);
	layout.addWidget(undoButton);
	layout.addWidget(redoButton);
	window.setLayout(&layout);

	connect(undoButton, &QPushButton::clicked, this, &GUI::UndoButtonClicked);
	connect(redoButton, &QPushButton::clicked, this, &GUI::RedoButtonClicked);

	QShortcut* undoShortcut = new QShortcut(QKeySequence("Ctrl+Z"), &window);
	QShortcut* redoShortcut = new QShortcut(QKeySequence("Ctrl+Y"), &window);

	QObject::connect(undoShortcut, &QShortcut::activated, this, &GUI::UndoButtonClicked);
	QObject::connect(redoShortcut, &QShortcut::activated, this, &GUI::RedoButtonClicked);

	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &GUI::AdminModeRunMode);
	return adminMenu->exec();
}

int GUI::printUserMenu()
{
	QStringList options;
	options << "HTML" << "CSV";
	bool ok;
	QString selectedOption = QInputDialog::getItem(nullptr, "Save Watchlist", "Choose file format:", options, 0, false, &ok);
	if (!ok)
	{
		return 0;
	}
	this->userMode.setEventList(selectedOption.toStdString());
	if (this->userMode.GetWatchList() == nullptr) {
		QMessageBox::critical(nullptr, "Error", "Watchlist is nullptr!");
		return 0;
	}
	QDialog* userMenu = new QDialog();
	QWidget window{ userMenu };
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1; font-size: 20px;");
	QVBoxLayout layout{};
	QListWidget list;
	QLabel title("User mode");
	title.setAlignment(Qt::AlignCenter);
	QListWidgetItem* element1 = new QListWidgetItem("1. Get events from a month", &list);
	QListWidgetItem* element2 = new QListWidgetItem("2. Delete event from eventlist", &list);
	QListWidgetItem* element3 = new QListWidgetItem("3. Print eventlist", &list);
	QListWidgetItem* element4 = new QListWidgetItem("4. Save watchlist", &list);
	QListWidgetItem* element5 = new QListWidgetItem("5. Open watchlist", &list);
	layout.addWidget(&title);
	layout.addWidget(&list);
	window.setLayout(&layout);
	window.show();
	window.resize(500, 450);
	connect(&list, &QListWidget::itemClicked, this, &GUI::UserModeRunMode);
	return userMenu->exec();
}

int GUI::addEvent() {
	QDialog* popup = new QDialog{};
	popup->setStyleSheet("background-color: #2C3E50; color: #ECF0F1; font-size: 20px;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Add a new event");
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("color: #ECF0F1;");

	QLabel titleLabel("Title ");
	QLabel descriptionLabel("Description ");
	QLabel dayLabel("Day ");
	QLabel monthLabel("Month ");
	QLabel hourLabel("Hour ");
	QLabel minuteLabel("Minute ");
	QLabel numberOfPeopleLabel("Number of people ");
	QLabel linkLabel("Link ");

	QLineEdit* titleEdit = new QLineEdit{};
	titleEdit->setObjectName("title");
	titleLabel.setBuddy(titleEdit);

	QLineEdit* descriptionEdit = new QLineEdit{};
	descriptionEdit->setObjectName("description");
	descriptionLabel.setBuddy(descriptionEdit);

	QLineEdit* dayEdit = new QLineEdit{};
	dayEdit->setObjectName("day");
	dayLabel.setBuddy(dayEdit);

	QLineEdit* monthEdit = new QLineEdit{};
	monthEdit->setObjectName("month");
	monthLabel.setBuddy(monthEdit);

	QLineEdit* hourEdit = new QLineEdit{};
	hourEdit->setObjectName("hour");
	hourLabel.setBuddy(hourEdit);

	QLineEdit* minuteEdit = new QLineEdit{};
	minuteEdit->setObjectName("minute");
	minuteLabel.setBuddy(minuteEdit);

	QLineEdit* numberOfPeopleEdit = new QLineEdit{};
	numberOfPeopleEdit->setObjectName("numberOfPeople");
	numberOfPeopleLabel.setBuddy(numberOfPeopleEdit);

	QLineEdit* linkEdit = new QLineEdit{};
	linkEdit->setObjectName("link");
	linkLabel.setBuddy(linkEdit);

	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleEdit);
	formLayout->addRow(&descriptionLabel, descriptionEdit);
	formLayout->addRow(&dayLabel, dayEdit);
	formLayout->addRow(&monthLabel, monthEdit);
	formLayout->addRow(&hourLabel, hourEdit);
	formLayout->addRow(&minuteLabel, minuteEdit);
	formLayout->addRow(&numberOfPeopleLabel, numberOfPeopleEdit);
	formLayout->addRow(&linkLabel, linkEdit);

	QPushButton* addButton = new QPushButton("Add");
	formLayout->addRow(addButton);
	connect(addButton, &QPushButton::clicked, this, &GUI::AddAdminButtonClicked);

	popup->setLayout(formLayout);
	popup->resize(500, 450);
	return popup->exec();
}

int GUI::deleteEventfromAdmin()
{
	QDialog* popup = new QDialog{};
	QWidget window{ popup };
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a event");
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("color: #ECF0F1;");

	QLabel titleLabel("Title ");
	QLabel linkLabel("Link ");

	QLineEdit* titleEdit = new QLineEdit{};
	titleEdit->setObjectName("title");
	titleLabel.setBuddy(titleEdit);

	QLineEdit* linkEdit = new QLineEdit{};
	linkEdit->setObjectName("link");
	linkLabel.setBuddy(linkEdit);

	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleEdit);
	formLayout->addRow(&linkLabel, linkEdit);

	QPushButton deleteButton("Delete");
	formLayout->addRow(&deleteButton);
	connect(&deleteButton, &QPushButton::clicked, this, &GUI::DeleteAdminButtonClicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int GUI::updateEvent()
{
	QDialog* popup = new QDialog{};
	QWidget window{ popup };
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Update a event");
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("color: #ECF0F1;");
	
	QLabel oldTitleLabel("Old Title ");
	QLabel oldLinkLabel("Old Link ");
	QLabel newTitleLabel("New Title ");
	QLabel newDescriptionLabel("New Description ");
	QLabel newDayLabel("New Day ");
	QLabel newMonthLabel("New Month ");
	QLabel newDateLabel("New Minute ");
	QLabel newTimeLabel("New Hour ");
	QLabel newNumberOfPeopleLabel("New Number of people ");
	QLabel newLinkLabel("New Link ");

	QLineEdit* oldTitleEdit = new QLineEdit{};
	oldTitleEdit->setObjectName("oldTitle");
    oldTitleLabel.setBuddy(oldTitleEdit);

	QLineEdit* oldLinkEdit = new QLineEdit{};
	oldLinkEdit->setObjectName("oldLink");
	oldLinkLabel.setBuddy(oldLinkEdit);

	QLineEdit* newTitleEdit = new QLineEdit{};
	newTitleEdit->setObjectName("newTitle");
	newTitleLabel.setBuddy(newTitleEdit);

	QLineEdit* newDescriptionEdit = new QLineEdit{};
	newDescriptionEdit->setObjectName("newDescription");
	newDescriptionLabel.setBuddy(newDescriptionEdit);

	QLineEdit* newDayEdit = new QLineEdit{};
	newDayEdit->setObjectName("day");
	newDateLabel.setBuddy(newDayEdit);

	QLineEdit* newMonthEdit = new QLineEdit{};
	newMonthEdit->setObjectName("month");
	newDateLabel.setBuddy(newMonthEdit);

	QLineEdit* newHourEdit = new QLineEdit{};
	newHourEdit->setObjectName("hour");
	newTimeLabel.setBuddy(newHourEdit);

	QLineEdit* newMinuteEdit = new QLineEdit{};
	newMinuteEdit->setObjectName("minute");
	newTimeLabel.setBuddy(newMinuteEdit);

	QLineEdit* newNumberOfPeopleEdit = new QLineEdit{};
	newNumberOfPeopleEdit->setObjectName("newNumberOfPeople");
	newNumberOfPeopleLabel.setBuddy(newNumberOfPeopleEdit);

	QLineEdit* newLinkEdit = new QLineEdit{};
	newLinkEdit->setObjectName("newLink");
	newLinkLabel.setBuddy(newLinkEdit);





	formLayout->addRow(&label);
    formLayout->addRow(&oldTitleLabel, oldTitleEdit);
	formLayout->addRow(&oldLinkLabel, oldLinkEdit);
	formLayout->addRow(&newTitleLabel, newTitleEdit);
	formLayout->addRow(&newDescriptionLabel, newDescriptionEdit);
	formLayout->addRow(&newDayLabel, newDayEdit);
	formLayout->addRow(&newMonthLabel, newMonthEdit);
	formLayout->addRow(&newTimeLabel, newHourEdit);
	formLayout->addRow(&newDateLabel, newMinuteEdit);
	formLayout->addRow(&newNumberOfPeopleLabel, newNumberOfPeopleEdit);
	formLayout->addRow(&newLinkLabel, newLinkEdit);



	QPushButton updateButton("Update");
	formLayout->addRow(&updateButton);
	connect(&updateButton, &QPushButton::clicked, this, &GUI::UpdateAdminButtonClicked);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int GUI::displayEvents()
{
	QDialog* popup = new QDialog{};
	QTableWidget* table = new QTableWidget(popup);


	QString tableStyleSheet = "background-color: #2C3E50; color: #ECF0F1;";
	table->setStyleSheet(tableStyleSheet);


	table->setRowCount(this->adminMode.getEvents().size());
	table->setColumnCount(8);

	QStringList headers;
	headers << "Title" << "Description" << "Day" << "Month" << "Hour" << "Minute" << "Number of people" << "Link";
	table->setHorizontalHeaderLabels(headers);


	int rowIndex = 0;
	for (const auto& event : this->adminMode.getEvents())
	{
		QTableWidgetItem* titleitem = new QTableWidgetItem(event.getTitle().c_str());
		QTableWidgetItem* descriptionitem = new QTableWidgetItem(event.getDescription().c_str());
		QTableWidgetItem* dayitem = new QTableWidgetItem(QString::number(event.getDate().day));
		QTableWidgetItem* monthitem = new QTableWidgetItem(QString::number(event.getDate().month));
		QTableWidgetItem* houritem = new QTableWidgetItem(QString::number(event.getTime().hour));
		QTableWidgetItem* minuteitem = new QTableWidgetItem(QString::number(event.getTime().minute));
		QTableWidgetItem* numberOfPeopleitem = new QTableWidgetItem(QString::number(event.getNumberOfPeople()));
		QTableWidgetItem* linkitem = new QTableWidgetItem(event.getLink().c_str());

		table->setItem(rowIndex, 0, titleitem);
		table->setItem(rowIndex, 1, descriptionitem);
		table->setItem(rowIndex, 2, dayitem);
		table->setItem(rowIndex, 3, monthitem);
		table->setItem(rowIndex, 4, houritem);
		table->setItem(rowIndex, 5, minuteitem);
		table->setItem(rowIndex, 6, numberOfPeopleitem);
		table->setItem(rowIndex, 7, linkitem);
		rowIndex++;
	}


	QHeaderView* header = table->horizontalHeader();
	header->setStyleSheet("color: #0f3139;");
	header->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);


	QHeaderView* verticalHeader = table->verticalHeader();
	verticalHeader->setStyleSheet("color: #0f3139;");
	verticalHeader->setDefaultAlignment(Qt::AlignRight | Qt::AlignVCenter);

	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->resizeRowsToContents();
	table->resizeColumnsToContents();
	table->resize(750, 500);


	table->show();


	return popup->exec();
}


int GUI::getEventsFromAMonth()
{
	QDialog dialog;
	QVBoxLayout layout(&dialog);
	dialog.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	QLabel searchLabel("Search a month:");
	QLineEdit eventLineEdit;
	QPushButton searchButton("Search");
	QGroupBox eventGroupBox("Details");
	QVBoxLayout eventLayout(&eventGroupBox);
	QLabel eventLabel;
	QPushButton addButton("Add to Eventlist");
	QPushButton nextButton("Next");
	searchButton.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	addButton.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	nextButton.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	QHBoxLayout searchLayout;
	searchLayout.addWidget(&searchLabel);
	searchLayout.addWidget(&eventLineEdit);
	searchLayout.addWidget(&searchButton);

	layout.addLayout(&searchLayout);
	layout.addWidget(&eventGroupBox);
	layout.addWidget(&addButton);
	layout.addWidget(&nextButton);

	std::vector<Event> Monthlyevents;
	int current_index = 0;

	QObject::connect(&searchButton, &QPushButton::clicked, [&]() {
		QString monthString = eventLineEdit.text();
		try {
			Validators::validateMonth(monthString.toInt());
		}
		catch (Exception& e)
		{
			displayError(e.what());
			return;
		}
		int month;
		if (monthString.isEmpty())
		{
			month = 0;
		}
		else month = monthString.toInt();
		Monthlyevents = this->userMode.GetEventsFromAMonth(this->adminMode.getEvents(), month);
		if (Monthlyevents.size() == 0)
		{
			eventLabel.setText("No events in this month!");
			return;
		}
		this->detailsEvent(Monthlyevents[current_index], eventLabel);
		//std::string command = "start " + Monthlyevents[current_index].getLink();
		//system(command.c_str());
		});
	QObject::connect(&addButton, &QPushButton::clicked, [&]() {
		if (current_index < Monthlyevents.size())
		{
			//this->userMode.AddEventToWatchList(Monthlyevents[current_index]);
			try {
				this->userMode.AddEventToWatchList(Monthlyevents[current_index]);
			}
			catch (Exception& e)
			{
				displayError(e.what());

			}

			this->adminMode.copyRepoAdmin(this->userMode.GetAllEvents());
			current_index++;
			if (current_index == Monthlyevents.size())
			{
				current_index = 0;
			}
			else this->detailsEvent(Monthlyevents[current_index], eventLabel);
			//std::string command = "start " + Monthlyevents[current_index].getLink();
			//system(command.c_str());

		}
		});
	QObject::connect(&nextButton, &QPushButton::clicked, [&]() {
		current_index++;
		if (current_index == Monthlyevents.size())
		{
			current_index = 0;
		}
		this->detailsEvent(Monthlyevents[current_index], eventLabel);
		//std::string command = "start " + Monthlyevents[current_index].getLink();
		//system(command.c_str());

		});
	eventLayout.addWidget(&eventLabel);
	dialog.resize(500, 250);
	return dialog.exec();
}

int GUI::removeEventFromEventList()
{
	QDialog* popup = new QDialog{};
	QWidget window{ popup };
	window.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	QFormLayout* formLayout = new QFormLayout{};
	QLabel label("Remove a event from eventlist");
	label.setAlignment(Qt::AlignCenter);
	label.setStyleSheet("color: #ECF0F1;");
	QLabel titleLabel("Title ");
	QLabel linkLabel("Link ");

	QLineEdit* titleEdit = new QLineEdit{};
	titleEdit->setObjectName("title");
	titleLabel.setBuddy(titleEdit);

	QLineEdit* linkEdit = new QLineEdit{};
	linkEdit->setObjectName("link");
	linkLabel.setBuddy(linkEdit);

	formLayout->addRow(&label);
	formLayout->addRow(&titleLabel, titleEdit);
	formLayout->addRow(&linkLabel, linkEdit);

	QPushButton deleteButton("Delete");
	formLayout->addRow(&deleteButton);
	connect(&deleteButton, &QPushButton::clicked, this, [&]() {
		std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
		std::string link = sender()->parent()->findChild<QLineEdit*>("link")->text().toStdString();

		try
		{
			this->userMode.RemoveEventFromWatchList(title, link);
			QDialog validationMessage;
			QLabel label("Event removed successfully!", &validationMessage);
			label.setAlignment(Qt::AlignCenter);
			label.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
			label.setFont(QFont("Courier", 15, 10));
			label.resize(350, 250);
			label.show();
			validationMessage.exec();

		}
		catch (Exception& e)
		{
			displayError(e.what());
			QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
			parent->close();
		}
		QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
		parent->close();
		}
	
	);
	window.setLayout(formLayout);
	window.show();
	return popup->exec();
}

int GUI::displayEventList() {
	QDialog* popup = new QDialog();
	QVBoxLayout* layout = new QVBoxLayout;

	std::vector<Event> events = this->userMode.GetWatchList()->getEvents();
	MyModel* model = new MyModel;
	model->setEvents(events);
	QTableView* view = new QTableView;
	view->setModel(model);
	view->setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	view->horizontalHeader()->setStyleSheet(
		"QHeaderView::section {"
		"background-color: #34495E; color: #ECF0F1; padding: 4px; }"
	);
	view->verticalHeader()->setStyleSheet(
		"QHeaderView::section {"
		"background-color: #34495E; color: #ECF0F1; padding: 4px; }"
	);


	layout->addWidget(view);
	popup->setLayout(layout);
	popup->resize(750, 500);
	popup->exec();
	return 0;
}

void GUI::detailsEvent(const Event& event, QLabel& label)
{
	Date date = event.getDate();
	Time time = event.getTime();
	QString title = QString::fromStdString(event.getTitle());
	QString description = QString::fromStdString(event.getDescription());
	QString link = QString::fromStdString(event.getLink());
	QString numberOfPeople = QString::number(event.getNumberOfPeople());
	QString day = QString::number(date.day);
	QString month = QString::number(date.month);
	QString hour = QString::number(time.hour);
	QString minute = QString::number(time.minute);

	QString message = QString("<b>Title:</b> %1<br><b>Description:</b> %2<br><b>Date:</b> %3.%4<br><b>Time:</b> %5:%6<br><b>Number of people:</b> %7<br><b>Link:</b> %8")
		.arg(title).arg(description).arg(day).arg(month).arg(hour).arg(minute).arg(numberOfPeople).arg(link);

	label.setText(message);
	label.setAlignment(Qt::AlignCenter);
	label.setWordWrap(true);
	label.setOpenExternalLinks(true);
	label.setTextInteractionFlags(Qt::TextBrowserInteraction);
	label.setStyleSheet("font-size: 20px;");
}

int GUI::saveEventListtoFile()
{
	this->userMode.saveWatchList();
	QMessageBox validationMessage;
	validationMessage.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	validationMessage.setText("EventList saved successfully!");
	return validationMessage.exec();
}

int GUI::openEventList()
{
	this->userMode.openWatchList();
	return 0;
}

void GUI::displayError(const char* message)
{
	if (strcmp(message, "invalid stoi argument") == 0)
		message = "Invalid input";
	QDialog* popup = new QDialog();
	QLabel label(message, popup);
	popup->setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
	label.setAlignment(Qt::AlignCenter);
	label.setFont(QFont("Courier", 15, 10));
	label.resize(350, 250);
	label.show();
	popup->exec();
}
void GUI::AddAdminButtonClicked()
{
	std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
	std::string description = sender()->parent()->findChild<QLineEdit*>("description")->text().toStdString();
	int numberOfPeople = sender()->parent()->findChild<QLineEdit*>("numberOfPeople")->text().toInt();
	std::string link = sender()->parent()->findChild<QLineEdit*>("link")->text().toStdString();
	std::string daystr = sender()->parent()->findChild<QLineEdit*>("day")->text().toStdString();
	std::string monthstr = sender()->parent()->findChild<QLineEdit*>("month")->text().toStdString();
	std::string hourstr = sender()->parent()->findChild<QLineEdit*>("hour")->text().toStdString();
	std::string minutestr = sender()->parent()->findChild<QLineEdit*>("minute")->text().toStdString();	

	
	Date date;
	Time time;

	date.day = std::stoi(daystr);
	date.month = std::stoi(monthstr);
	time.hour = std::stoi(hourstr);
	time.minute = std::stoi(minutestr);

	
	try
	{
		Validators::validateDate(date);
		Validators::validateNumberOfPeople(numberOfPeople);
		Validators::validateTime(time);
		this->adminMode.addEvent(title, description, date, time, numberOfPeople, link);
		QDialog validationMessage;
		QLabel label("Event added successfully!", &validationMessage);
		label.setAlignment(Qt::AlignCenter);
		label.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
		label.setFont(QFont("Courier", 15, 10));
		label.resize(300, 200);
		label.show();
		validationMessage.exec();
	}
	catch (Exception& e)
	{
		displayError(e.what());
		QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
		parent->close();
	}
	
	QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
	parent->close();


}

void GUI::DeleteAdminButtonClicked()
{
	std::string title = sender()->parent()->findChild<QLineEdit*>("title")->text().toStdString();
	std::string link = sender()->parent()->findChild<QLineEdit*>("link")->text().toStdString();

	try
	{	
		this->adminMode.deleteEvent(title, link);
		QDialog validationMessage;
		QLabel label("Event removed successfully!", &validationMessage);
		label.setAlignment(Qt::AlignCenter);
		label.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
		label.setFont(QFont("Courier", 15, 10));
		label.resize(350, 250);
		label.show();
		validationMessage.exec();
	}
	catch (Exception& e)
	{
		displayError(e.what());
		QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
		parent->close();
	}
	QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
	parent->close();
}

void GUI::UpdateAdminButtonClicked()
{
	std::string oldTitle = sender()->parent()->findChild<QLineEdit*>("oldTitle")->text().toStdString();
	std::string oldLink = sender()->parent()->findChild<QLineEdit*>("oldLink")->text().toStdString();
	std::string newTitle = sender()->parent()->findChild<QLineEdit*>("newTitle")->text().toStdString();
	std::string newDescription = sender()->parent()->findChild<QLineEdit*>("newDescription")->text().toStdString();
	int newNumberOfPeople = sender()->parent()->findChild<QLineEdit*>("newNumberOfPeople")->text().toInt();
	std::string newLink = sender()->parent()->findChild<QLineEdit*>("newLink")->text().toStdString();
	std::string day = sender()->parent()->findChild<QLineEdit*>("day")->text().toStdString();
	std::string month = sender()->parent()->findChild<QLineEdit*>("month")->text().toStdString();
	std::string hour = sender()->parent()->findChild<QLineEdit*>("hour")->text().toStdString();
	std::string minute = sender()->parent()->findChild<QLineEdit*>("minute")->text().toStdString();



	Date date;
	Time time;

	date.day = std::stoi(day);
	date.month = std::stoi(month);

	time.hour = std::stoi(hour);
	time.minute = std::stoi(minute);




	try
	{
		Validators::validateDate(date);
		Validators::validateNumberOfPeople(newNumberOfPeople);
		Validators::validateTime(time);

		this->adminMode.updateEvent(oldTitle, oldLink, newTitle, newDescription, date, time, newNumberOfPeople, newLink);
		QDialog validationMessage;
		QLabel label("Event updated successfully!", &validationMessage);
		label.setAlignment(Qt::AlignCenter);
		label.setStyleSheet("background-color: #2C3E50; color: #ECF0F1;");
		label.setFont(QFont("Courier", 15, 10));
		label.resize(350, 250);
		label.show();
		validationMessage.exec();
	}
	catch (Exception& e)
	{
		displayError(e.what());
		QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
		parent->close();
	}
	QWidget* parent = qobject_cast<QWidget*>(sender()->parent());
	parent->close();

}

void GUI::UserModeRunMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); //clicked item
	QString text = item->currentItem()->text();
	try {
		if(text.startsWith("1"))
			this->getEventsFromAMonth();
		else if (text.startsWith("2"))
			this->removeEventFromEventList();
		else if (text.startsWith("3"))
			this->displayEventList();
		else if (text.startsWith("4"))
			this->saveEventListtoFile();
		else if (text.startsWith("5"))
			this->openEventList();
	}
	catch (Exception& e)
	{
		displayError(e.what());
	}
}

void GUI::AdminModeRunMode()
{
	QListWidget* item = qobject_cast<QListWidget*>(QObject::sender()); //clicked item
	QString text = item->currentItem()->text();
	try {
		if (text.startsWith("1"))
			this->addEvent();
		else if (text.startsWith("2"))
			this->deleteEventfromAdmin();
		else if (text.startsWith("3"))
			this->updateEvent();
		else if (text.startsWith("4"))
			this->displayEvents();
	}
	catch (Exception& e)
	{
		displayError(e.what());
	}
}

void GUI::UndoButtonClicked()
{
	try
	{
		this->adminMode.executeUndo();
	}
	catch (Exception& e)
	{
		QMessageBox::critical(nullptr, "Error", e.what());

	}

}

void GUI::RedoButtonClicked()
{
	try
	{
		this->adminMode.executeRedo();
	}
	catch (Exception& e)
	{
		QMessageBox::critical(nullptr, "Error", e.what());
	}
}

