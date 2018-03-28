#include "Constants.h"
#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;

	//Sprite Rendering Telemetry
	xPosition = 0.f;
	yPosition = 0.0f;
	angle = 0.0f;

	commandAngle = 0.0f;
	xVelocity = 0.0f;
	yVelocity = 0.0f;

	//Animation Values
	stepLagCount = 0;
	stepCount = 0;
	spriteID = 0;

	command = "";
}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
	texture->free();
}

bool GameObject::Initialize(SDL_Renderer* renderer, std::string path)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	//Load the Art Asset
	texture = new Texture();
	texture->load(renderer, path);

	//Construct clipping sequence
	for (int i = 0; i<NUM_SPRITES; i++) {

		int row = i / SPRITE_SHEET_NCOLS;
		int col = i%SPRITE_SHEET_NCOLS;

		clipArray[i].x = col*SPRITE_WIDTH;
		clipArray[i].y = row*SPRITE_HEIGHT;
		clipArray[i].w = SPRITE_WIDTH;
		clipArray[i].h = SPRITE_HEIGHT;
	}

	//Load Font
	font = TTF_OpenFont("./Assets/Fonts/impact.ttf", 48);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	return(true);
}

void GameObject::HandleEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT:
			commandAngle = -360.0f / 100.f;
			command = "left";
			break;
		case SDLK_RIGHT:
			commandAngle = 360.0f / 100.f;
			command = "right";
			break;
		case SDLK_UP:
			xVelocity = 1.0f;
			yVelocity = 1.0f;
			command = "up";
			break;
		case SDLK_DOWN:
			xVelocity = 0.0f;
			yVelocity = 0.0f;
			command = "down";
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

	//Update the Animation Every ANIM_LAG frames (cheat to avoid more comlicated
	//timing issues while demonstrating animation)
	stepLagCount++;
	stepLagCount %= ANIM_LAG;
	if (stepLagCount == 0)
	{
		stepCount++;
		stepCount %= ANIM_SIZE;
		spriteID = ANIMATION[stepCount];
	}
}

void GameObject::Draw()
{
	//Call the Render command with a NON-NULL clip.  This selects a sprite from
	//the sprite sheet that is valid.
	texture->renderEx(renderer, (int)xPosition, (int)yPosition, angle, &clipArray[spriteID]);

	if (command != "")
	{
		//Render Command to Text
		SDL_Color textColor = { 255, 255, 51 };
		SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, command.c_str(), textColor));

		//Set rendering space and render to screen
		int width = 0, height = 0;
		SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);
		SDL_Rect renderQuad = { (Uint32)xPosition, (Uint32)yPosition - 80, width, height };

		//Render to screen
		SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad);

		//Reset command
		command = "";
	}
}
