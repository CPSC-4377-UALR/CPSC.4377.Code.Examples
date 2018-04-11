#include "Constants.h"
#include "NPC.h"
#include "Blackboard.h"
#include "SpriteComponent.h"
#include "GameObject.h"



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

void NPC::Initialize(Task * behaviorTree, Blackboard* blackboard)
{
	this->behaviorTree = behaviorTree;
	//set the initial position for this object.
	blackboard->enemyOrigins[owner] = owner->GetComponent<Sprite>()->position;
}

void NPC::Update()
{
}

void NPC::Finish()
{
	delete behaviorTree;
}
