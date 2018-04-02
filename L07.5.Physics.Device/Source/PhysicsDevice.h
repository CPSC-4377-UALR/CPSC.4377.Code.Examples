#pragma once
#include "Constants.h"
#include "Box2D.h"
class GameObject;

class PhysicsDevice
{
public:
	PhysicsDevice(GAME_VEC gravity);
	bool initialize();
	bool createFixture(GameObject* object, GAME_PHYSICS physics);
	
	GAME_VEC getPosition(GameObject* object);
	GAME_FLT getAngle(GameObject* object);

	void applyForce(GameObject* object, bool forward);
	void applyAngularForce(GameObject* object, bool right);

	bool update(float dt);
	b2Body* findBody(GameObject* object);
	
	bool removeObject(GameObject* object);

	//conversions between phsysics world and SDL2
	GAME_VEC PV2GV(b2Vec2 physicsVec);
	inline float PW2RW(GAME_FLT x) { return x*fPRV; }
	inline float RW2PW(GAME_FLT x) { return x / fPRV; }
	//inline float RW2PW(GAME_INT x) { return (float)x / fPRV; }
	inline float RW2PWAngle(GAME_FLT x) { return((float)x*(2.0f*PI) / 360.0f); } //degrees to radians
	inline float PW2RWAngle(GAME_FLT x) { return((float)x*360.0f / (2.0f*PI)); } //radians to degrees

	//public just for creating borders!
	b2World* world;
private:
	
	const b2Vec2 gravity;
	GAME_VEC alignCenters(GameObject* object);
};