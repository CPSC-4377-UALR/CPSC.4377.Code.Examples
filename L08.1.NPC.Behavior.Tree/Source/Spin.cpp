#include "Spin.h"



Spin::Spin()
{
}


Spin::~Spin()
{
}

bool Spin::initiailize()
{
	return false;
}

void Spin::run()
{
	//grab the component that own's the tree, then that component's object, then the sprite component, 
	//and finally the angle.
	owner->GetOwner()->GetComponent<Sprite>()->angle++;
	success();
}
