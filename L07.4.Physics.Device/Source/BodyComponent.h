#ifndef BODY_H
#define BODY_H

#include "Component.h"
#include "Constants.h"
#include "PhysicsDevice.h"

class BodyComponent : public Component
{
public:
	BodyComponent(GameObject* owner);
	~BodyComponent();

	bool initialize(GAME_PHYSICS physics, PhysicsDevice* pDevice);
	
	void Start() {}
	void Update() {};
	void Finish();

	GAME_FLT getAngle();
	GAME_VEC getPosition();

	void applyForce(bool  forward);
	void applyAngularForce(bool right);
protected:
	PhysicsDevice* pDevice;
	
};

#endif