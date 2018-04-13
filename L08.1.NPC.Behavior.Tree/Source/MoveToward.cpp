#include "MoveToward.h"
#include "BehaviorTree.h"
#include "Component.h"
#include "GameObject.h"
#include "SpriteComponent.h"


MoveToward::MoveToward() :LeafTask()
{
}

MoveToward::MoveToward(BehaviorTree * tree, Task * control):LeafTask(tree, control)
{
	
}


MoveToward::~MoveToward()
{
}

bool MoveToward::initiailize(bool * conditional, GAME_VEC * goal)
{
	if (conditional != nullptr && goal != nullptr)
	{
		this->conditional = conditional;
		this->goal = goal;
	}
	else
		return false;
}

void MoveToward::run()
{
	if (*conditional)
	{
		float forceMultiplier = 2;
		GAME_VEC* position = &(owner->GetOwner()->GetComponent<Sprite>()->position);
		float angle = owner->GetOwner()->GetComponent<Sprite>()->angle;
		position->x += (cosf(angle*PI / 180) - (PI / 2))*forceMultiplier;
		position->y += (sinf(angle*PI / 180) - (PI / 2))*forceMultiplier;
		success();
	}
	else
	{
		fail();
	}
}
