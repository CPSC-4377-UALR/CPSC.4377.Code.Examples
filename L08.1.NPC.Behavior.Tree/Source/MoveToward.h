#pragma once
#include "LeafTask.h"
#include "Constants.h"
class MoveToward :
	public LeafTask
{
public:
	MoveToward();
	~MoveToward();
	
	bool initiailize(bool* conditional, GAME_VEC* goal);

	void run(); //contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
};

