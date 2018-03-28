#include "GameObject.h"

GameObject::GameObject()
{
	renderer = NULL;
}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
}

bool GameObject::Initialize(SDL_Renderer* renderer, std::string path)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	return(true);
}

void GameObject::HandleEvent(SDL_Event* event)
{

}

void GameObject::Update()
{


}

void GameObject::Draw()
{

	//
	// DRAW USING SDL2 Primitives
	//

	//Draw empty red rectangle
	SDL_Rect rect; rect.x = 200, rect.y = 250, rect.w = 50, rect.h = 50;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);
	SDL_RenderDrawRect(renderer, &rect);

	//Draw filled green rectangle
	rect.x = 300, rect.y = 300, rect.w = 100, rect.h = 100;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
	SDL_RenderFillRect(renderer, &rect);

	//Draw some blue lines.
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(renderer, 50, 50, 200, 200);
	SDL_RenderDrawLine(renderer, 200, 200, 0, 333);

	//Draw some white lines.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawLine(renderer, 0, 0, 200, 200);
	SDL_RenderDrawLine(renderer, 200, 200, 400, 0);;

	//Draw some white points.
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderDrawPoint(renderer, 500, 500);
	SDL_RenderDrawPoint(renderer, 500, 525);

	//
	// DRAW USING SDL2_gfx Primitives
	//

	//Draw White Line
	lineRGBA(renderer, 450, 450, 375, 350, 255, 255, 255, 255);

	//Draw Red Elipse
	filledEllipseRGBA(renderer, 500, 50, 20, 15, 255, 0, 0, 255);

	//Draw Blue Polygon
	Sint16 xCoords[] = { 100, 200,250,15 };
	Sint16 yCoords[] = { 100, 100,120,200 };
	filledPolygonRGBA(renderer, xCoords, yCoords, 4, 0, 0, 255, 255);

}
