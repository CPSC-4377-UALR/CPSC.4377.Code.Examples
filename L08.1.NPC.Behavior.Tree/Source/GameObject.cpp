#include "Constants.h"
#include "GameObject.h"
#include "Texture.h"
#include "Component.h"
#include "SpriteComponent.h"
#include "NPC.h"
#include "UserInputComponent.h"

GameObject::GameObject()
{
	initialized = false;
}

GameObject::~GameObject()
{
}

bool GameObject::Initialize(GraphicsDevice * gDevice, std::string type, std::string path)
{

	Sprite* sprite = new Sprite(this);
	sprite->Initialize(gDevice, path);
	AddComponent(sprite);

	if (type == "player")
	{
		UserInput* userInput = new UserInput(this);

		userInput->Initialize();
		AddComponent(userInput);
	}
	else
	{
		NPC* npc = new NPC(this);
		npc->Initialize();
		AddComponent(npc);
	}
	
	

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

