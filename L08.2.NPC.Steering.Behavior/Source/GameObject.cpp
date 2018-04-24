#include <iostream>
#include "GameObject.h"
#include "Texture.h"

using namespace std;

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;
	spritePosition = { 300.0f, 400.0f };
	mousePosition = { 0.0f, 0.0f };
	angle = 90;
	velocity = 5.0f;
	spriteVector = { 2.0f, 0.0f };
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
	switch (event->type)
	{
	case SDL_MOUSEMOTION:
		//Get coordinates of the event
		mousePosition = { (float)event->motion.x, (float)event->motion.y };
		break;
	}

	//cout << "mouse: (" << mousePosition.x << ", " << mousePosition.y << ")" << endl;
}

void GameObject::Update()
{
	float targetAngle = (std::atan2(mousePosition.y - spritePosition.y, mousePosition.x - spritePosition.x) * 180 / PI);
	float diff = targetAngle - angle - 90;

	while (diff < -180) {
		diff += 360;
	}
	while (diff > 180) {
		diff -= 360;
	}
	if (diff < 0 && velocity >0)
	{
		angle += 3;
	}
	else if (diff > 0 && velocity > 0)
	{
		angle -= 3;
	}
	float approach = distance(mousePosition, spritePosition);
	if (approach > 300)
	{
		velocity = 8;
	}
	else if (approach <= 300 && approach >= 10)
	{
		velocity = 4;
	}
	else if (approach < 10 && velocity > 0)
	{
		velocity --;
	}

	spriteVector =
	{
		(float)cosf(angle*PI / 180 - PI / 2)*velocity,
		(float)sinf(angle*PI / 180 - PI / 2)*velocity
	};
	spritePosition += spriteVector;

}

void GameObject::Draw()
{
	texture->renderEx(renderer,(int)spritePosition.x,(int)spritePosition.y,angle,NULL);
}

float GameObject::distance(GAME_VEC src1, GAME_VEC src2)
{
	GAME_VEC diff = src1 - src2;
	return sqrt(diff.x*diff.x + diff.y*diff.y);
}


