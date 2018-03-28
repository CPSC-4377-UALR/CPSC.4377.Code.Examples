#include <sstream>
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
	height = 0.0f;
	width = 0.0f;

	//Interaction Values
	xCursor = 0;
	yCursor = 0;
	spriteID = 0;
	up = true;

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
	case SDL_MOUSEMOTION:
		//Get coordinates of the event
		xCursor = event->motion.x;
		yCursor = event->motion.y;
		break;
	case SDL_MOUSEBUTTONDOWN:
		//Set state variable of mouse down
		up = false;
		break;
	case SDL_MOUSEBUTTONUP:
		//Set state variable of mouse down
		up = true;
		break;
	default:
		;
	}
}

void GameObject::Update()
{

	//Define sprite boundaries
	float xmin = xPosition;
	float ymin = yPosition;
	float xmax = xmin + clipArray[spriteID].w;
	float ymax = ymin + clipArray[spriteID].h;

	//Determine is cursor is over object
	bool active = false;
	if (xCursor >= xmin && xCursor <= xmax)
	{
		if (yCursor >= ymin && yCursor <= ymax)
		{
			active = true;
		}
	}

	//Mouse not over (not selected)
	if (!active && up)
	{
		spriteID = DEFAULT;
	}

	//Mouse over (not selected)
	if (active && up)
	{
		spriteID = ACTIVE;
	}

	//Mouse over + select (not selected)
	if (active && !up)
	{
		spriteID = SELECT;
	}


}

void GameObject::Draw()
{
	//Call the Render command with a NON-NULL clip.  This selects a sprite from
	//the sprite sheet that is valid.
	texture->renderEx(renderer, (int)xPosition, (int)yPosition, 0, &clipArray[spriteID]);

	std::stringstream sstream;
	sstream << xCursor << ", " << yCursor;
	std::string command = sstream.str();

	if (command.c_str() != "")
	{
		//Render Command to Text
		SDL_Color textColor = { 255, 255, 255 };
		SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, command.c_str(), textColor));

		//Set rendering space and render to screen
		int width = 0, height = 0;
		SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);
		SDL_Rect renderQuad = { (Uint32)xPosition + 200, (Uint32)yPosition, width, height };

		//Render to screen
		SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad);

	}
}
