#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<memory>
#include<iostream>
#include<vector>
#include "SDL.h"
//#include "SpriteComponent.h"

class Component;
class Sprite;
class UserInput;
class GraphicsDevice;

class GameObject
{

public:
	GameObject();
	~GameObject();


	bool Initialize(GraphicsDevice* gDevice, std::string);

	void AddComponent(Component* component);

	template<class T>
	T* GetComponent()
	{
		for (auto comp : components)
		{
			T* target = nullptr;
			if (target = dynamic_cast<T*>(comp))
			{
				return(target);
			}
		}

		//Return NULL;
		return(nullptr);
	}

	void Update();
	SDL_Event* event;
protected:
	
	std::vector<Component*> components;
	bool initialized;

};

#endif

//#ifndef GAMEOBJECT_H
//#define GAMEOBJECT_H
//
//#include<iostream>
//#include "Constants.h"
//#include "SDL.h"
//#include "SDL_ttf.h"
//
//
//
//class Texture;
//
//class GameObject
//{
//public:
//	GameObject();
//	~GameObject();
//	bool Initialize(SDL_Renderer*, std::string);
//	void HandleEvent(SDL_Event*);
//	void Update();
//	void Draw();
//
//protected:
//	SDL_Renderer* renderer;
//	Texture* texture;
//	SDL_Rect clipArray[NUM_SPRITES];
//
//	float xPosition;
//	float yPosition;
//	float angle;
//
//	float commandAngle;
//	float xVelocity;
//	float yVelocity;
//
//	Uint32 stepLagCount;
//	Uint32 stepCount;
//	Uint32 spriteID;
//
//	std::string command;
//
//	TTF_Font* font;
//
//};
//
//#endif