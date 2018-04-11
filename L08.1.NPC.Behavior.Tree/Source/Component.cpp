#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject* owner) : owner(owner) {}

Component::~Component() {}

void Component::OwnerDestroyed()
{
	Finish();
	owner = nullptr;
}


GameObject* Component::GetOwner()
{
	return(owner);
}