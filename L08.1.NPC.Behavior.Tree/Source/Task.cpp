#include "Task.h"



Task::Task()
{
}

Task::Task(GameObject * owner)
{
	this->owner = owner;
	currTask = this;
}


Task::~Task()
{
}
