#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "SDL.h"

#include "SDL2_gfxPrimitives.h"

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
};

#endif