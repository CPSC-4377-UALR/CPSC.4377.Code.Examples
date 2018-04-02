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
#include "SDL.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "GameObject.h"
#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "PhysicsDevice.h"
#include "Box2D/Box2D.h"

using namespace std;
int main(int argc, char *argv[])
{

	float dt = 1.0 / 50.0f;
	//Construct Graphical Device
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;
	GraphicsDevice* gDevice = new GraphicsDevice(SCREEN_WIDTH, SCREEN_HEIGHT);
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
	if (!fps->Initialize(1/dt)) {
		printf("Frame Timer could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}
	
	//Construct Physics Device
	GAME_VEC gravity{ 0,500 };
	PhysicsDevice* pDevice = new PhysicsDevice(gravity);
	if (!pDevice->initialize())
	{
		printf("Physics Device could not initialize!");
		exit(1);
	}

	//create boundaries!
	//Set boundaries of world (Render->Physics)
	const b2Vec2 vTopLeft = b2Vec2(pDevice->RW2PW(0), pDevice->RW2PW(0));
	const b2Vec2 vTopRight = b2Vec2(pDevice->RW2PW(SCREEN_WIDTH), pDevice->RW2PW(0));
	const b2Vec2 vBottomLeft = b2Vec2(pDevice->RW2PW(0), pDevice->RW2PW(SCREEN_HEIGHT));
	const b2Vec2 vBottomRight = b2Vec2(pDevice->RW2PW(SCREEN_WIDTH), pDevice->RW2PW(SCREEN_HEIGHT));

	b2BodyDef bd;
	b2Body* edge = pDevice->world->CreateBody(&bd);
	b2EdgeShape shape;
	
	//Create bottom boundary
	shape.Set(vBottomLeft, vBottomRight);
	edge->CreateFixture(&shape, 0);

	//Create left boundary
	shape.Set(vBottomLeft, vTopLeft);
	edge->CreateFixture(&shape, 0);

	//Create right boundary
	shape.Set(vBottomRight, vTopRight);
	edge->CreateFixture(&shape, 0);

	//Initialize Game Object
	GameObject* object = new GameObject();
	object->Initialize(gDevice, pDevice, "./Assets/Images/Megaman.png");

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
		GAME_VEC position = object->GetComponent<BodyComponent>()->getPosition();
		cout << position.x << ", " << position.y << endl;
		pDevice->update(dt);
		position = object->GetComponent<BodyComponent>()->getPosition();
		cout << position.x << ", " << position.y << endl;
		object->Update();
		

		//
		//Game state updates complete, let's draw
		//
		gDevice->Begin();

		if (object->GetComponent<Sprite>() != nullptr)
		{
			object->GetComponent<Sprite>()->Draw();
		}

		//End the frame and draw to window
		gDevice->Present();

		//Buffer the Frames per second (if necessary)
		fps->fpsRegulate();

	}

	return 0;

}