#include "Task.h"
#include "Blackboard.h"

Blackboard* Task::blackboard = nullptr;

Task::Task()
{
	control = nullptr;
	tree = nullptr;
	owner = nullptr;
}

Task::Task(BehaviorTree * tree, Task * control)
{
	this->tree = tree;
	this->control = control;
}

Task::Task(Component * owner) :Task()
{
	this->owner = owner;
}


Task::~Task()
{
}

void Task::start()
{
	
}

void Task::end()
{
}

void Task::resetTask()
{
	status = FRESH;

}

void Task::running()
{
	control->childRunning();
	status = RUNNING;	
}

void Task::success()
{
	control->childSuccess();
	status = SUCEEDED;
	end();
}

void Task::fail()
{
	control->childFail();
	status = FAILED;
	end();
}

void Task::cancel()
{
	if(status == RUNNING)
		status = CANCELLED;
}

bool Task::addChild(Task * childTask)
{
	return (addChildToTask(childTask));
}
