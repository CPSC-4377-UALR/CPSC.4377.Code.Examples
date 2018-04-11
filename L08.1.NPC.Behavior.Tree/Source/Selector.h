#pragma once
#include "BranchTask.h"
class Selector :
	public BranchTask
{
public:
	Selector();
	~Selector();
	void run();//contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
	
protected:
	void childSuccess(); //called when one of the children of the task succeeds.
	void childFail(); //called when one of the children of the task fails.
	void childRunning(); //called when one of the children of the task needs to run again.
	

};

