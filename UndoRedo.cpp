#include "UndoRedo.h"
#include <iostream>

AddCommand::AddCommand(Repository *repository, Event event){
	this->repository = repository;
	this->events.push_back(event);
}

void AddCommand::redo()
{
	Event event_to_add = this->events[0];
	try {
				this->repository->addEvent(event_to_add);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}

}

void AddCommand::undo()
{
	Event event_to_remove = this->events[0];
	try {
		int index = this->repository->findEvent(event_to_remove);
		this->repository->deleteEvent(index);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}
}
RemoveCommand::RemoveCommand(Repository *repository, Event event){
	this->repository = repository;
	this->events.push_back(event);
}

void RemoveCommand::redo()
{
	Event event_to_remove = this->events[0];
	try {
		int index = this->repository->findEvent(event_to_remove);
		this->repository->deleteEvent(index);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}
}

void RemoveCommand::undo()
{
	Event event_to_add = this->events[0];
	try {
		this->repository->addEvent(event_to_add);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}
}
UpdateCommand::UpdateCommand(Repository *repository, Event event_old, Event event_new) {

	this->repository =  repository;
	this->events.push_back(event_old);
	this->events.push_back(event_new);
}

void UpdateCommand::redo()
{
	Event event_to_update = this->events[1];
	try {
		int index = this->repository->findEvent(this->events[0]);
		this->repository->updateEvent(index, event_to_update);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}
}

void UpdateCommand::undo()
{
	Event event_to_update = this->events[0];
	try {
		int index = this->repository->findEvent(this->events[1]);
		this->repository->updateEvent(index, event_to_update);
	}
	catch (Exception& e){
		std::cout << e.what() << '\n';
	}
}

void UndoRedo::addOperation(Command* command)
{
	this->undoStack.push(command);
}

void UndoRedo::executeUndo()
{
	if (this->undoStack.empty())
		throw Exception("No more undos!");
	Command* command = this->undoStack.top();
	command->undo();
	this->redoStack.push(command);
	this->undoStack.pop();
}

void UndoRedo::executeRedo()
{
	if (this->redoStack.empty())
		throw Exception("No more redos!");
	Command* command = this->redoStack.top();
	this->undoStack.push(command);
	command->redo();
	this->redoStack.pop();
}
Command::Command() {
	this->repository = nullptr;
}
