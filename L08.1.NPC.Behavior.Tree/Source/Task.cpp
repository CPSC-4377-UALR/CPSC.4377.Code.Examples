#include "Task.h"
#include "Blackboard.h"

Blackboard* Task::blackboard = nullptr;

Task::Task()
{
}

Task::Task(Component * owner)
{
	this->owner = owner;
}


Task::~Task()
{
}

void Task::resetTask()
{
	status = FRESH;
}

void Task::running()
{
	status = RUNNING;	
}

void Task::success()
{
	status = SUCEEDED;
}

void Task::fail()
{
	status = FAILED;
}

void Task::cancel()
{
	status = CANCELLED;
}

bool Task::addChild(Task * childTask)
{
	return (addChildToTask(childTask));
}
