/*
* Author:	Keith Bush
*			UALR
*
* Date:		January 31, 2015
*
* File:		Source.cpp
*
* Purpose:	Demonstrate initializing SDL, generating an empty graphics window, and
*			gracefully shutting down the program.
*/

#include <iostream>

#include "SDL.h"
#include "GraphicsDevice.h"
#include "GameObject.h"

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

	//Initialize
	GameObject* object = new GameObject();
	object->Initialize(gDevice->getRenderer(), "./Assets/Images/PlayerPaper.png");

	//Initialize Termination Criteria
	bool quit = false;

	//While the user hasn't quit
	while (quit == false)
	{

		//Poll Event
		SDL_PollEvent(event);

		//Translate Event to QUIT signal
		if (event->type == SDL_QUIT)
		{
			quit = true;
		}

		SDL_Delay(1000);


		//Start the frame
		gDevice->Begin();

		//Draw a game object
		object->Draw();

		//End the frame and draw to window
		gDevice->Present();

	}


	return 0;

}