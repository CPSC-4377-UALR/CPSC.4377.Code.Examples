#include "Constants.h"
#include "GameObject.h"
#include "Texture.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "UserInputComponent.h"
#include "BodyComponent.h"

GameObject::GameObject()
{
	initialized = false;
}

GameObject::~GameObject()
{
}

bool GameObject::Initialize(GraphicsDevice * gDevice, PhysicsDevice* pDevice, std::string path)
{
	//add sprite component
	Sprite* sprite = new Sprite(this);
	sprite->Initialize(gDevice, path);
	AddComponent(sprite);

	//add user input component
	UserInput* userInput = new UserInput(this);
	userInput->Initialize();
	AddComponent(userInput);

	BodyComponent* body = new BodyComponent(this);
	body->initialize({ 0, GAME_DYNAMIC, GAME_RECTANGLE,0.1f,0.5f,0.9f,0.0f,0.0f,0.0f,true }, pDevice);
	AddComponent(body);

	//Call the start method
	if (!initialized)
	{
		for (auto comp : components)
		{
			comp->Start();
		}
		initialized = true;
	}

	return(initialized);
}

void GameObject::AddComponent(Component * component)
{
	components.push_back(component);
}





void GameObject::Update()
{
	for (auto component : components)
	{
		component->Update();
	}
	
}

