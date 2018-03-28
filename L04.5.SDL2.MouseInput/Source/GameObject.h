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

	//Object properties
	float xPosition;
	float yPosition;
	float width;
	float height;

	//Interaction properties
	Uint32 xCursor;
	Uint32 yCursor;
	Uint32 spriteID;
	bool up;

	TTF_Font* font;

};

#endif