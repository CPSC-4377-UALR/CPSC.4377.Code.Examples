#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "SDL.h"

class Texture;

class GameObject
{
public:
	GameObject();
	~GameObject();
	bool Initialize(SDL_Renderer*, std::string);
	void Draw();

protected:
	SDL_Renderer* renderer;
	Texture* texture;

};

#endif