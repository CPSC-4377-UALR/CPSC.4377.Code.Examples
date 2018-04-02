#include "UserInputComponent.h"
#include "BodyComponent.h"
#include "GameObject.h"

UserInput::UserInput(GameObject * owner) :Component(owner)
{

}

UserInput::~UserInput()
{
}

void UserInput::Initialize()
{
}

void UserInput::HandleEvent(SDL_Event * event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT:
			right = false;
			turn = true;
			command = "left";
			break;
		case SDLK_RIGHT:
			right = true;
			turn = true;
			command = "right";
			break;
		case SDLK_UP:
			forward = true;
			back = false;
			turn = false;
			command = "up";
			break;
		case SDLK_DOWN:
			back = true;
			forward = false;
			turn = false;
			command = "down";
			break;
		}
	}
}

void UserInput::Update()
{
	HandleEvent(_owner->event);
	BodyComponent* body = _owner->GetComponent<BodyComponent>();
	//forward = true;
	if (turn)
	{
		body->applyAngularForce(right);
//		turn = false;
	}
	if (forward)
	{
		body->applyForce(forward);
	//	forward = false;
	}
	if (back)
	{
		body->applyForce(false);
		//back = false;
	}



}

void UserInput::Finish()
{
}

void UserInput::Start()
{
}
