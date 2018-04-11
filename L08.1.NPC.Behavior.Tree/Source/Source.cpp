/*
* Author:	Keith Bush
*			UALR
*
* Date:		February 1, 2015
*
* File:		Source.cpp
*
* Purpose:	Demonstrate basic animation of sprites, frame timing, and
*           rotation capabilities of rendering.
*/

#include <iostream>
#include <vector>
#include "SDL.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "Blackboard.h"
#include "Task.h"

int main(int argc, char *argv[])
{
	//Construct Graphical Device
	GraphicsDevice* gDevice = new GraphicsDevice(800, 600);
	if (!gDevice->Initialize(true))
	{
		printf("Graphics Device could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	//Construct Event
	SDL_Event* event = new SDL_Event();
	if (!event) {
		printf("SDL Event could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	//Construct Frame Timer
	Timer* fps = new Timer();
	if (!fps->Initialize(100)) {
		printf("Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	
	std::vector<GameObject*> objects;
	//Initialize Game Object
	GameObject* object = new GameObject();
	object->Initialize(gDevice, "player", "./Assets/Images/Megaman.png");
	objects.push_back(object);
	GameObject* object2 = new GameObject();
	object2->Initialize(gDevice, "enemy", "./Assets/Images/Megaman.png");
	objects.push_back(object2);

	Task::blackboard = new Blackboard();
	Task::blackboard->objects = objects;
	//Initialize Termination Criteria
	bool quit = false;

	//While the user hasn't quit
	while (!quit)
	{

		//Start the frame's time
		fps->start();

		//Check for an event
		if (SDL_PollEvent(event))
		{
			//Translate Event to QUIT signal
			if (event->type == SDL_QUIT)
			{
				quit = true;
			}
		}

		//
		//Object handles relevant events
		//
		object->event = event;

		//
		//Conduct the update (i.e., physics/animation)
		//
		object->Update();
		object2->Update();

		//
		//Game state updates complete, let's draw
		//
		gDevice->Begin();

		if (object->GetComponent<Sprite>() != nullptr)
		{
			object->GetComponent<Sprite>()->Draw();
		}
		if (object2->GetComponent<Sprite>() != nullptr)
		{
			object2->GetComponent<Sprite>()->Draw();
		}
		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}

	return 0;

}