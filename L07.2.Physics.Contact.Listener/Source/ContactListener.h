#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include"Constants.h"
#include"SDL.h"
#include "Box2D/Box2D.h"


class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact){}

	void EndContact(b2Contact* contact){}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
	{
        //Grab the two Physics Bodies involved in the Contact
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

        //Conduct a modification
		if(bodyA->GetType() == b2_dynamicBody)
			bodyA->SetLinearVelocity(b2Vec2(RW2PW(-300),RW2PW(-100)));
		else
			bodyB->SetLinearVelocity(b2Vec2(RW2PW(300), RW2PW(300)));
	}

	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse){}
};

#endif