#ifndef CONSTANTS_H
#define CONSTANTS_H

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;

struct GAME_VEC
{
	float x;
	float y;
};

enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };

typedef struct GAME_PHYSICS
{
	GAME_FLT spinSpeed;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE objectShape;
	GAME_FLT density;
	GAME_FLT friction;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	GAME_FLT force;
	bool physicsOn;
}GAME_PHYSICS;

//Constants
const GAME_FLT PI = 3.14159f;
const float fPRV = 10.0f;

//Sprite ID Update Constants
const int ANIM_LAG = 5;
const int ANIM_SIZE = 3;
const int ANIMATION[] = { 27, 51, 75 };

//Sprite Sheet Constants
const int NUM_SPRITES = 96;
const int SPRITE_HEIGHT = 60;
const int SPRITE_WIDTH = 47;
const int SPRITE_SHEET_NCOLS = 24;
const int SPRITE_SHEET_NROWS = 4;

#endif