#include "Constants.h"
#include "NPC.h"
#include "Blackboard.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Selector.h"
#include "Sequence.h"
#include "Task.h"
#include "MoveToward.h"
#include "TurnToward.h"
#include "Spin.h"
#include "BehaviorTree.h"
#include "BranchTask.h"

NPC::NPC()
{
}

NPC::NPC(GameObject * owner)
{
	this->owner = owner;
}


NPC::~NPC()
{
}

void NPC::Initialize()
{
	//set the initial position for this object.
	Task::blackboard->enemyOrigins[owner] = owner->GetComponent<Sprite>()->position;
	
	//create behavior tree
	behaviorTree = new BehaviorTree(this);
	
		//root of tree is a selector
		Selector* decideBehavior = new Selector();
		behaviorTree->addChild(decideBehavior);

		//add sequences (in order) to selector
		Sequence* chaseEnemy = new Sequence();
		decideBehavior->addChild(chaseEnemy);

			//add leaf tasks to sequence
			TurnToward* turnTowardEnemy = new TurnToward();
			chaseEnemy->addChild(turnTowardEnemy);

			MoveToward* moveTowardEnemy = new MoveToward();
			chaseEnemy->addChild(moveTowardEnemy);
		
		Sequence* returnToOrigin = new Sequence();
		decideBehavior->addChild(returnToOrigin);
			//add leaf tasks to sequence
			TurnToward* turnTowardEnemy = new TurnToward();
			returnToOrigin->addChild(turnTowardEnemy);

			MoveToward* moveTowardEnemy = new MoveToward();
			returnToOrigin->addChild(moveTowardEnemy);
			
		Spin* patrol = new Spin();
		patrol->initiailize();
		decideBehavior->addChild(patrol);
		

	


}

void NPC::Update()
{
}

void NPC::Finish()
{
	delete behaviorTree;
}
