#pragma once
#include "LeafTask.h"
#include "Constants.h"
class TurnToward :
	public LeafTask
{
public:
	TurnToward();
	TurnToward(BehaviorTree* tree, Task* control);
	~TurnToward();
	bool initiailize(bool* conditional, GAME_VEC* goal);

	void run(); //contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
	

private:
	bool* conditional;
	GAME_VEC* goal;
};

