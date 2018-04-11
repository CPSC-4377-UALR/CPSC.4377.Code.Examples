#include "TurnToward.h"



TurnToward::TurnToward()
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
	if (conditional)
	{


	}
	else
		fail();
}
