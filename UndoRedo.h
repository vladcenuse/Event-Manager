#pragma once
#include "Event.h"
#include "Repository.h"
#include "Exception.h"
#include <stack>

class Command {
protected:
	std::vector<Event> events;
	Repository* repository;
public:
	Command();
	virtual void redo() = 0;
	virtual void undo() = 0;
};

class AddCommand : public Command {
public:
	AddCommand(Repository *repository, Event event);
	void redo() override;
	void undo() override;

};

class RemoveCommand : public Command {
public:
	RemoveCommand(Repository *repository, Event event);
	void redo() override;
	void undo() override;
};

class UpdateCommand : public Command {
public:
	UpdateCommand(Repository *repository, Event event_old, Event event_new);
	void redo() override;
	void undo() override;
};

class UndoRedo {
private:
		std::stack<Command*> undoStack;
		std::stack<Command*> redoStack;
public:
		UndoRedo() = default;
		void addOperation(Command* command);
		void executeUndo();
		void executeRedo();

};