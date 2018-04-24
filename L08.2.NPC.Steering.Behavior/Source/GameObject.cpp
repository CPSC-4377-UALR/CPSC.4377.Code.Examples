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

}

void GameObject::Update()
{
	//code based on: https://gamedev.stackexchange.com/questions/141606/gradually-rotate-vector-towards-another-vector/141612
	//find angle between mouse and ship
	float targetAngle = (std::atan2(mousePosition.y - spritePosition.y, mousePosition.x - spritePosition.x) * 180 / PI);
	
	//compare to ship's angle. the -90 is to adjust the sprite. Depending on you sprite, your may need to adjust this
	float diff = targetAngle - angle - 90;

	//ensures we don't go mor than 180 degres.
	while (diff < -180) {
		diff += 360;
	}
	while (diff > 180) {
		diff -= 360;
	}
		//adjust angle of sprite
	//&&'s are to avoid the sprite from shaking as it is lined up with the mouse or stopped
	if (diff < -2 && velocity >0)
	{
		angle += velocity/2;
	}
	else if (diff > 0 && diff < 179 && velocity > 0)
	{
		angle -= velocity/2;
	}
	angle %= 360;
	
	//use distance formula to figure out how far the mouse is from the sprite.
	float approach = distance(mousePosition, spritePosition);

	//slow down as we get closer, speed up as we get further
	if (approach > 200)
	{
		velocity = 10;
	}
	else if (approach <= 200 && approach >= 50)
	{
		if (velocity >4 )
			velocity -=1;
	}
	else if (approach < 50 && velocity > 0)
	{
		velocity -=0.2;
	}
	
	//figure force to apply
	spriteVector =
	{
		(float)cosf(angle*PI / 180 - PI / 2)*velocity,
		(float)sinf(angle*PI / 180 - PI / 2)*velocity
	};
	//cout << "force vec: " << spriteVector << endl;
	//apply force. += for GAME_VEC is overloaded in header file.
	spritePosition += spriteVector;
	//cout << "position: " << spritePosition << endl;
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

//ostream & operator<<(ostream & o, const GameObject::GAME_VEC & src)
//{
//	o << "(" << src.x << ", " << src.y << ")";
//	return o;
//	
//}
