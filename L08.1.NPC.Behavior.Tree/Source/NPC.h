#pragma once
#include "Component.h"
class Task;
class GameObject;
class Blackboard;
class NPC :
	public Component
{
public:
	NPC();
	NPC(GameObject* owner);
	~NPC();

	void Initialize();

	void Start() {}
	void Update();
	void Finish();
private:
	BehaviorTree* behaviorTree;
};

