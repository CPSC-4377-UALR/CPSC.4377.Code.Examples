#include "BodyComponent.h"

BodyComponent::BodyComponent(GameObject * owner) :Component(owner){}
BodyComponent::~BodyComponent() {}

bool BodyComponent::initialize(GAME_PHYSICS physics, PhysicsDevice* pDevice)
{
	//save the phsyics device
	this->pDevice = pDevice;
	//Create fixture.
	pDevice->createFixture(_owner, physics);
	return true;
}

void BodyComponent::Finish()
{
	pDevice->removeObject(_owner);
}

GAME_FLT BodyComponent::getAngle()
{
	return pDevice->getAngle(_owner);
}

GAME_VEC BodyComponent::getPosition()
{
	return pDevice->getPosition(_owner);
}

void BodyComponent::applyForce(bool forward)
{
	pDevice->applyForce(_owner, forward);
}

void BodyComponent::applyAngularForce(bool right)
{
	pDevice->applyAngularForce(_owner, right);
}
