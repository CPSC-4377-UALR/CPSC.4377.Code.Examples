#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "Constants.h"
#include "SDL.h"
#include "SDL_ttf.h"



class Texture;

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool Initialize(SDL_Renderer*, std::string);
	void HandleEvent(SDL_Event*);
	void Update();
	void Draw();

protected:
	SDL_Renderer* renderer;
	Texture* texture;
	SDL_Rect clipArray[NUM_SPRITES];

	float xPosition;
	float yPosition;
	float angle;

	float commandAngle;
	float xVelocity;
	float yVelocity;

	Uint32 stepLagCount;
	Uint32 stepCount;
	Uint32 spriteID;

	std::string command;

	TTF_Font* font;

};

#endif