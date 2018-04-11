#pragma once
#include <map>
#include <vector>
#include "Constants.h"
class GameObject;
class Blackboard
{
public:
	Blackboard();
	~Blackboard();
	GAME_VEC* playerPosition;
	std::map<GameObject*, GAME_VEC> enemyOrigins;
	std::vector<GameObject*> objects;
	bool attack;
};

