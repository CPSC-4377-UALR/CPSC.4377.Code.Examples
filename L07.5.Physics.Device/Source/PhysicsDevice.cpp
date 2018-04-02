#include "PhysicsDevice.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Texture.h"
#include "Constants.h"

PhysicsDevice::PhysicsDevice(GAME_VEC gravity) :gravity(RW2PW(gravity.x), RW2PW(+gravity.y))
{
}

//**************************************
//Creates a new world on initialization
bool PhysicsDevice::initialize()
//**************************************
{
	world = new b2World(gravity);
	if (world == nullptr) return false;
	return true;
}

//**************************************
//Steps the physics world
bool PhysicsDevice::update(float dt)
//**************************************
{
	world->Step(dt, 8, 3);
	return true;
}

//**************************************
//Creates a body and fixture for a passed in object
//based on passed in values
bool PhysicsDevice::createFixture
(
	GameObject* object,
	GAME_PHYSICS physics
)
//**************************************
{
	//need the sprite component first!
	if (object->GetComponent<Sprite>() == nullptr) return false;
	//new body definition
	b2BodyDef* bd = new b2BodyDef;
	

	
	
	//Set userData field with passed in object pointer.
	//void* so we can store anything! But must cast back to what it is to use!
	bd->userData = object;


	//set body type
	switch (physics.bodyType)
	{
	case GAME_STATIC:
		bd->type = b2_staticBody;
		break;
	case GAME_KINEMATIC:
		bd->type = b2_kinematicBody;
		break;
	case GAME_DYNAMIC:
		bd->type = b2_dynamicBody;
		break;
	}

	//********Adjust postion because SDL is top left, while box2d is center*************
	//Texture* texture = object->GetComponent<Sprite>()->getTexture();
	//subtract off half the width.
	GAME_VEC position{ 800/2,600/2};
	//**********************************************************************************

	// set starting position & angle
	bd->position.Set(RW2PW(position.x), RW2PW(position.y));
	bd->angle = RW2PWAngle(0);

	//add the body to the world
	b2Body* body = world->CreateBody(bd);

	//Set damping values on the body
	//body->SetAngularDamping(physics.angularDamping);
	//body->SetLinearDamping(physics.linearDamping);
	
	//Fixture definition
	b2FixtureDef shapefd;
	//made need one or the other, depending on what was passed.
	b2PolygonShape pShape;
	b2CircleShape cShape;
	//Set fixture's shape
	switch (physics.objectShape)
	{
	case GAME_RECTANGLE:
		//rectangle's dimensions
		pShape.SetAsBox(RW2PW(position.x), RW2PW(position.y));
		shapefd.shape = &pShape;
		break;
	case GAME_CIRCLE:
		//circle radius based on object's width.
		GAME_FLT width = object->GetComponent<Sprite>()->getTexture()->getWidth() / 2.0f;
		GAME_FLT height = object->GetComponent<Sprite>()->getTexture()->getHeight() / 2.0f;

		if (width > height)	cShape.m_radius = (RW2PW(width));
		else cShape.m_radius = (RW2PW(height));
		shapefd.shape = &cShape;
		break;
	}

	//set fixture values based on passed in values.
	shapefd.density = physics.density;
	shapefd.friction = physics.friction;
	shapefd.restitution = physics.restitution;

	//create the fixture on the body.
	body->CreateFixture(&shapefd);
	body->SetActive(physics.physicsOn);

	return true;

}

GAME_VEC PhysicsDevice::getPosition(GameObject * object)
{
	return (alignCenters(object));
}

GAME_FLT PhysicsDevice::getAngle(GameObject * object)
{
	
	return (PW2RWAngle(findBody(object)->GetAngle()));
}

void PhysicsDevice::applyForce(GameObject* object, bool forward)
{
	int forceMultiplier = 10;
	b2Vec2 applyForce;
	forward = true;
	if (forward)
	{
		applyForce.x = (cosf(getAngle(object)*PI / 180) - (PI / 2))*forceMultiplier;
		applyForce.y = (sinf(getAngle(object)*PI / 180) - (PI / 2))*forceMultiplier;
	}
	else
	{
		applyForce.x = (cosf(getAngle(object)*PI / 180) + (PI / 2))*forceMultiplier;
		applyForce.y = (sinf(getAngle(object)*PI / 180) + (PI / 2))*forceMultiplier;
	}
	findBody(object)->ApplyLinearImpulse(applyForce, findBody(object)->GetWorldCenter(), true);
}

void PhysicsDevice::applyAngularForce(GameObject * object, bool right)
{
	float forceMultiplier = 1;
	if (!right) forceMultiplier *= -1;
	forceMultiplier = findBody(object)->GetAngularVelocity() + (forceMultiplier*2.0f*(1 / 50));
	findBody(object)->SetAngularVelocity(forceMultiplier);
}

b2Body * PhysicsDevice::findBody(GameObject * object)
{
	for (b2Body* body = world->GetBodyList(); body; body = body->GetNext())
	{
		//when we have a match, return it.
		if (object == body->GetUserData())
		{
			return body;
		}
	}
	//if there was no match, return nullptr
	return nullptr;
}

bool PhysicsDevice::removeObject(GameObject * object)
{
	//Find the body based on the passed object
	b2Body* body = findBody(object);

	//check to see if we have a body.
	if (body == nullptr)
	{
		return false;
	}
	else
	{
		//delete the body from the world
		world->DestroyBody(body);
		return true;
	}
}

GAME_VEC PhysicsDevice::PV2GV(b2Vec2 physicsVec)
{
	return { PW2RW(physicsVec.x), PW2RW(physicsVec.y) };
}

GAME_VEC PhysicsDevice::alignCenters(GameObject * object)
{
	//needed for position in physics world
	b2Vec2 physPosition = findBody(object)->GetPosition();
	//needed for width/height of object;
	//Texture* texture = object->GetComponent<Sprite>()->getTexture();
	
	//adjust x & y positions by half the sprite's width and heigh respectively to get the top left corner!
	GAME_VEC position{ PW2RW(physPosition.x) - (SPRITE_WIDTH / 2), PW2RW(physPosition.y) - (SPRITE_HEIGHT / 2) };
	return (position);
}
