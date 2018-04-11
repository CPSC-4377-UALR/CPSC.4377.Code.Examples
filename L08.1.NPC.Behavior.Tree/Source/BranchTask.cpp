#include "BranchTask.h"



BranchTask::BranchTask()
{
}


BranchTask::~BranchTask()
{
}

void BranchTask::resetTask()
{
	for (auto task : children)
	{
		task->resetTask();
	}
}

bool BranchTask::addChildToTask(Task * childTask)
{
	if (childTask != nullptr)
	{
		children.push_back(childTask);
		return true;
	}
	else return false;
}

int BranchTask::getChildCount()
{
	return children.size();
}

Task * BranchTask::getChild(int index)
{
	if (index <= getChildCount())
	{
		return (children[index]);
	}
	else
	{
		return nullptr;
	}
}
