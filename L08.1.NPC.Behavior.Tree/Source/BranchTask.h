#pragma once
#include "Task.h"
class BranchTask :
	public Task
{
public:
	BranchTask();
	BranchTask(BehaviorTree* tree, Task* control);
	~BranchTask();
	void run();//contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
	void resetTask();
	
protected:
	bool addChildToTask(Task* childTask); //adds a child to the list of this task's children. It is called by the final method addChild() mentioned below.
	int getChildCount(); //returns the number of children of the task.
	Task* getChild(int index); //returns the child at the given index

	std::vector<Task*> children; //all the children for the branch

};

