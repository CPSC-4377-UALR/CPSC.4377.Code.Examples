#include "GameObject.h"
#include "Component.h"

Component::Component(GameObject* owner) : _owner(owner) {}

Component::~Component() {}

void Component::OwnerDestroyed()
{
	Finish();
	_owner = nullptr;
}


GameObject* Component::GetOwner()
{
	return(_owner);
}