#include "BehaviorTree.h"
#include "Component.h"
#include "Task.h"



BehaviorTree::BehaviorTree()
{
	root = nullptr;
}

BehaviorTree::BehaviorTree(Component * owner):Task(owner)
{
	
}


BehaviorTree::~BehaviorTree()
{
}

void BehaviorTree::resetTask()
{
	root->resetTask();
}

void BehaviorTree::run()
{
	if(root->getStatus()!=CANCELLED)
		root->run();
}

bool BehaviorTree::addChildToTask(Task * childTask)
{
	if (root == nullptr)
		root = childTask;
	else
		return false;
	return true;
}

Task * BehaviorTree::getChild(int index)
{
	if (index == 0)
	{
		return root;
	}
	else return nullptr;
}
