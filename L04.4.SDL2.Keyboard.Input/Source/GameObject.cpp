#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;
	xPosition = 0.f;
	yPosition = 0.0f;
	angle = 0.0f;
	commandAngle = 0.0f;
	xVelocity = 0.0f;
	yVelocity = 0.0f;
}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
	texture->free();
}

bool GameObject::Initialize(SDL_Renderer* renderer,std::string path)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	//Load the Art Asset
	texture = new Texture();
	texture->load(renderer,path);

	return(true);
}

void GameObject::HandleEvent(SDL_Event* event)
{
	switch(event->type)
	{
	case SDL_KEYDOWN:
		switch(event->key.keysym.sym)
		{
		case SDLK_LEFT:
			commandAngle = -360.0f/100.f;
			break;
		case SDLK_RIGHT:
			commandAngle = 360.0f/100.f;
			break;
		case SDLK_UP:
			xVelocity = 1.0f;
			yVelocity = 1.0f;
			break;
		case SDLK_DOWN:
			xVelocity = 0.0f;
			yVelocity = 0.0f;
			break;
		}
	}
}

void GameObject::Update()
{
	//Quasi-physics updates
	xPosition += xVelocity;
	yPosition += yVelocity;
	angle += commandAngle;

	//Set commandAngle to 0 to avoid frustrated steering.
	commandAngle = 0.0f;
}

void GameObject::Draw()
{
	texture->renderEx(renderer,(int)xPosition,(int)yPosition,angle,NULL);
}
