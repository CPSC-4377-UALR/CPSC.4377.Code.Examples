#pragma once
#include "Task.h"
class LeafTask :
	public Task
{
public:
	LeafTask();
	~LeafTask();
		
protected:
	//overloading virtual functions, but leaf tasks do not need any of these!
	void childSuccess() {}
	void childFail() {}
	void childRunning() {}
	bool addChildToTask(Task* childTask) {}
	int getChildCount() {}
	Task* getChild(int index) {}
};

