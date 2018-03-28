#include "Constants.h"
#include "Texture.h"
#include "GameObject.h"

GameObject::GameObject()
{
	renderer = NULL;
	texture = NULL;

	body = NULL;

	command = "";

	initialized = false;
}

GameObject::~GameObject()
{
	//Unhook renderer from object
	renderer = NULL;
	texture->free();
	texture = NULL;
}

bool GameObject::Initialize(SDL_Renderer* renderer, std::string path, b2World* world)
{
	//Assign the renderer for  this object
	this->renderer = renderer;

	//Load the Art Asset
	texture = new Texture();
	texture->load(renderer, path);

	//Initialize the SDL_ttf

	//Load Font
	font = TTF_OpenFont("./Assets/Fonts/impact.ttf", 48);
	if (font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//
	//Initialize Physics
	//
	//1. Define Body!
	//	a. dynamic - Will interact and can be interacted with and can move. i.e. player and enemies
	//	b. kinematic - will interact, CAN NOT be interacted with, and can move. i.e. moving platform
	//  c.static - will interact, cannot be interacted with, and CAN NOT move!! i.e. ground and walls
	
	bd.type = b2_dynamicBody;
	//initial position
	bd.position.Set(RW2PW(200), RW2PW(0));
	//initial angle SDL2 uses degrees while box2D uses radians. RW2PWAngle translates from degrees to radians!
	bd.angle = RW2PWAngle(60.0f);
	//Register Body with Physics World. body is a member of this class (not good practice. 
	body = world->CreateBody(&bd);  
	//userData is a void* and can store anything! great for finding the body back later!
	body->SetUserData(this);

	//Set up physics shape. There are several. Box is a rectangle and the height and width are the distance from the center to the edge. i.e. the radii of the rectangle
	shape.SetAsBox(RW2PW(texture->getWidth() / 2.0f), RW2PW(texture->getHeight() / 2.0f)); //Requires half widths
	
	//Set up physics fixture (shape, density, restitution)
	shapefd.shape = &shape;

	//the denser it is, the more gravity effects it!
	shapefd.density = 0.1f;
	//The higher the friction, the more velocity is lost when it rubs along something
	shapefd.friction = 0.5f;
	//how "bouncy" something is. in other words, how much force is returned to an object that runs into it.
	shapefd.restitution = 0.9f;

	//A body can have multiple fixture that have different properties.
	//more fixtures means more detailed physics, but more CPU usuage!
	body->CreateFixture(&shapefd); //Register fixture with physics world

	initialized = true;
	return(initialized);
}

void GameObject::HandleEvent(SDL_Event* event)
{
	switch (event->type)
	{
	case SDL_KEYDOWN:
		switch (event->key.keysym.sym)
		{
		case SDLK_LEFT:
			command = "left";
			break;
		case SDLK_RIGHT:

			command = "right";
			break;
		}
	}
}


void GameObject::Update(float dt)
{

	if (command == "left")
	{
		body->SetAngularVelocity(body->GetAngularVelocity() - 2.0f*dt);
	}

	if (command == "right")
	{
		body->SetAngularVelocity(body->GetAngularVelocity() + 2.0f*dt);
	}

}

void GameObject::Draw()
{

	//Convert Physics World Position to Render World Position
	b2Vec2 position = body->GetPosition();
	float drawX = PW2RW(position.x) - texture->getWidth() / 2.0f;
	float drawY = PW2RW(position.y) - texture->getHeight() / 2.0f;
	float32 angle = body->GetAngle();

	//Render to the Screen
	texture->renderEx(renderer, (int)drawX, (int)drawY, PW2RWAngle(angle), NULL);

	if (command != "")
	{

		//Render Command to Text
		SDL_Color textColor = { 255, 255, 51 };
		SDL_Texture* textSheetTexture = SDL_CreateTextureFromSurface(renderer, TTF_RenderText_Solid(font, command.c_str(), textColor));

		//Set rendering space and render to screen
		int width = 0, height = 0;
		SDL_QueryTexture(textSheetTexture, NULL, NULL, &width, &height);
		SDL_Rect renderQuad = { (Uint32)PW2RW(position.x),(Uint32)PW2RW(position.y) - 80, width, height };

		//Render to screen
		SDL_RenderCopy(renderer, textSheetTexture, NULL, &renderQuad);

		//Reset command
		command = "";
	}
}
