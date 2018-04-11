#pragma once
#include <vector>
class GameObject;
class Task 
{
public:
	Task();
	~Task();

	bool initialize(std::vector<Task*> tasks);

	virtual void run() = 0; //contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
	virtual void childSuccess() = 0; //called when one of the children of the task succeeds.
	virtual void childFail() = 0; //called when one of the children of the task fails.
	virtual void childRunning() = 0; //called when one of the children of the task needs to run again.
	virtual void addChildToTask(Task* childTask) = 0; //adds a child to the list of this task's children. It is called by the final method addChild() mentioned below.
	virtual int getChildCount() = 0; //returns the number of children of the task.
	virtual Task* getChild(int index)=0; //returns the child at the given index

	virtual void start(); // called when the task is entered, just before run() is invoked.
	virtual void end(); //called when the task is exited through success(), fail() or cancel(). This means that this task's status has just been set to SUCCEEDED, FAILED or CANCELLED respectively.
	
	bool running(); //called in run() to inform the parent that this task needs to run again. The task status is set to RUNNING.
	bool success(); //called in run() to inform the parent that this task has finished running with a success result. The task status is set to SUCCEEDED.
	bool fail(); //called in run() to inform the parent that this task has finished running with a failure result. The task status is set to FAILED.
	bool cancel(); //terminates this task and all its running children. This method MUST be called only if this task is running. The task status is set to CANCELLED.
	bool addChild(Task* childTask); //adds a child by invoking addChildToTask().
	
	static enum STATUS { FRESH, RUNNING, FAILED, SUCEEDED, CANCELLED };

protected:
	STATUS status;
	std::vector<Task*> tasks;

private:
	Task* currTask;
};

