#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;
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

	return(true);
}

void GameObject::Draw()
{
	texture->render(renderer, 0, 0, NULL);
}
