#pragma once
#include "Event.h"
#include "Exception.h"
class Validators
{
public:
	static void validateDate(Date date) {
		if (date.day < 1 || date.day > 30 || date.month < 1 || date.month > 12)
			throw Exception("Invalid date!");
	}

	static void validateTime(Time time) {
		if (time.hour < 0 || time.hour > 23 || time.minute < 0 || time.minute > 59)
			throw Exception("Invalid time!");
	}
	static void validateMonth(int month) {
		if (month < 0 || month > 12)
			throw Exception("Invalid month!");
	}
	static void validateNumberOfPeople(int numberOfPeople) {
		if (numberOfPeople < 0)
			throw Exception("Invalid number of people!");
	}
};
