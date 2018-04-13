#pragma once
#include "LeafTask.h"
#include "Component.h"
#include "GameObject.h"
#include "SpriteComponent.h"

class Spin :
	public LeafTask
{
public:
	Spin();
	Spin(BehaviorTree* tree, Task* control);
	~Spin();
	bool initiailize();

	void run(); //contains the update logic of the task. The actual implementation MUST call running(), success() or fail() exactly once.
};

