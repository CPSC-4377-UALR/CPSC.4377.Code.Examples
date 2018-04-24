#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<iostream>
#include "SDL.h"

class Texture;

class GameObject
{
public:
	struct GAME_VEC
	{
		float x;
		float y;
		GAME_VEC& operator+= (const GAME_VEC & src1)
		{
			this->x = src1.x + this->x;
			this->y = src1.y + this->y;
			return *this;
		}
		friend GAME_VEC operator+ (const GAME_VEC & src1, const GAME_VEC & src2)
		{
			return GAME_VEC{ src1.x + src2.x, src1.y + src2.y };
		}
		friend GAME_VEC operator- (const GAME_VEC & src1, const GAME_VEC & src2)
		{
			return GAME_VEC{ src1.x - src2.x, src1.y - src2.y };
		}
		friend bool operator> (const GAME_VEC & src1, int src2)
		{
			if (src1.x > src2 && src1.y > src2)
			{
				return true;
			}
			return false;
		}
		friend bool operator< (const GAME_VEC & src1, int src2)
		{
			if (src1.x < src2 && src1.y < src2)
			{
				return true;
			}
			return false;
		}
		friend bool operator== (const GAME_VEC & src1, const GAME_VEC & src2)
		{
			if (src1.x == src2.x && src1.y == src2.y)
			{
				return true;
			}
			return false;
		}
		friend GAME_VEC abs(GAME_VEC & src)
		{
			return { abs(src.x),abs(src.y) };
		}
	};
	GameObject();
	~GameObject();
	bool Initialize(SDL_Renderer*,std::string);
	void HandleEvent(SDL_Event*);
	void Update();
	void Draw();

protected:
	float distance(GAME_VEC, GAME_VEC);
	SDL_Renderer* renderer;
	Texture* texture;
	
	GAME_VEC spritePosition;
	GAME_VEC mousePosition;
	int angle;
	float velocity;
	float commandAngle;
	GAME_VEC spriteVector;
	const float PI = 3.14159f;
};

#endif