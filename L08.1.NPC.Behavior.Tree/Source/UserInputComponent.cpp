#include "UserInputComponent.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "Blackboard.h"

UserInput::UserInput(GameObject * owner) :Component(owner)
{

}

UserInput::~UserInput()
{
}

void UserInput::Initialize(Blackboard* blackboard)
{
	//puts the memory location of the player's position in the blackboar, so that it will always be upated!
	blackboard->playerPosition = &(owner->GetComponent<Sprite>()->position);
}

void UserInput::HandleEvent(SDL_Event * event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT:
			commandAngle = -360.0f / 100.f;
			command = "left";
			break;
		case SDLK_RIGHT:
			commandAngle = 360.0f / 100.f;
			command = "right";
			break;
		case SDLK_UP:
			xVelocity = 1.0f;
			yVelocity = 1.0f;
			command = "up";
			break;
		case SDLK_DOWN:
			xVelocity = 0.0f;
			yVelocity = 0.0f;
			command = "down";
			break;
		}
	}
}

void UserInput::Update()
{
	HandleEvent(owner->event);
	Sprite* sprite = owner->GetComponent<Sprite>();

	//Quasi-physics updates
	sprite->xPosition += xVelocity;
	sprite->yPosition += yVelocity;
	sprite->angle += commandAngle;

	////Set commandAngle to 0 to avoid frustrated steering.
	commandAngle = 0.0f;


}

void UserInput::Finish()
{
}

void UserInput::Start()
{
}
