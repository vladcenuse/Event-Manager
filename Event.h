#pragma once
#include <string>
#include "StringTokenizer.h"

struct Date
{
	int day;
	int month;
};
struct Time
{
	int hour;
	int minute;
};

class Event
{
private:
	std::string title;
	std::string description;
	Date date;
	Time time;
	int numberOfPeople;
	std::string link;

public:
	// constructor
	Event() : title{ "" }, description{ "" }, date{ 0,0 }, time{ 0,0 }, numberOfPeople{ 0 }, link{ "" } {}
	Event(std::string title, std::string description, Date date, Time time, int numberOfPeople, std::string link);

	// getters
	std::string getTitle() const;
	std::string getDescription() const;
	Date getDate() const;
	Time getTime() const;
	int getNumberOfPeople() const;
	std::string getLink() const;

	// setters
	void setTitle(std::string new_title);
	void setDescription(std::string new_description);
	void setDate(Date new_date);
	void setTime(Time new_time);
	void setNumberOfPeople(int new_numberOfPeople);
	void setLink(std::string new_link);

	bool operator==(const Event& event_to_compare);
	void operator=(const Event& event_to_copy);
	friend std::istream& operator>>(std::istream& input, Event& event_to_read);
	friend std::ostream& operator<<(std::ostream& output, const Event& event_to_write);

};