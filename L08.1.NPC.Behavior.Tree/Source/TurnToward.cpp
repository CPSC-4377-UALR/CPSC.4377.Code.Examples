#include "TurnToward.h"
#include "BehaviorTree.h"
#include "Component.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Blackboard.h"

TurnToward::TurnToward()
{
}

TurnToward::TurnToward(BehaviorTree * tree, Task * control) :LeafTask(tree, control)
{
}


TurnToward::~TurnToward()
{
}

bool TurnToward::initiailize(bool * conditional, GAME_VEC * goal)
{
	this->conditional = conditional;
	this->goal = goal;
	status = FRESH;
	return false;
}

void TurnToward::run()
{
	if (*conditional)
	{
		float* angle = &(owner->GetOwner()->GetComponent<Sprite>()->angle);
		GAME_VEC position = owner->GetOwner()->GetComponent<Sprite>()->position;
		*angle = atanf((goal->y - position.y) / (goal->x / position.x));
		success();
	}
	else
		fail();
}
