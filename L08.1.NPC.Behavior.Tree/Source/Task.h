#pragma once
#include <vector>

class GameObject;
class Blackboard;
class BehaviorTree;
class Component;

class Task 
{
public:
	Task();
	Task(Component* owner);
	~Task();

	virtual void run() = 0; //contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
	

	virtual void start(); // called when the task is entered, just before run() is invoked.
	virtual void end(); //called when the task is exited through success(), fail() or cancel(). This means that this task's status has just been set to SUCCEEDED, FAILED or CANCELLED respectively.
	virtual void resetTask(); //this task to make it restart from scratch on next run. The task is cancelled if it was running. In any case the task status is set to FRESH.
	
	void running(); //called in run() to inform the parent that this task needs to run again. The task status is set to RUNNING.
	void success(); //called in run() to inform the parent that this task has finished running with a success result. The task status is set to SUCCEEDED.
	void fail(); //called in run() to inform the parent that this task has finished running with a failure result. The task status is set to FAILED.
	void cancel(); //terminates this task and all its running children. This method MUST be called only if this task is running. The task status is set to CANCELLED.
	bool addChild(Task* childTask); //adds a child by invoking addChildToTask().
	
	static enum STATUS { FRESH, RUNNING, FAILED, SUCEEDED, CANCELLED };
	static Blackboard* blackboard;

	STATUS getStatus() { return status; }	

protected:
	virtual void childSuccess() = 0; //called when one of the children of the task succeeds.
	virtual void childFail() = 0; //called when one of the children of the task fails.
	virtual void childRunning() = 0; //called when one of the children of the task needs to run again.
	virtual bool addChildToTask(Task* childTask) = 0; //adds a child to the list of this task's children. It is called by the final method addChild() mentioned below.
	virtual int getChildCount() = 0; //returns the number of children of the task.
	virtual Task* getChild(int index) = 0; //returns the child at the given index
	
	STATUS status;

	Task* control; //it's the parent of the task. It's set to null when the task's status is FRESH; set to the parent otherwise.
	BehaviorTree* tree; //it's the reference to the behavior tree the task belongs to. Like the control property, it's set to null when the task's status is FRESH; set to the tree otherwise.

	Component* owner;
};

