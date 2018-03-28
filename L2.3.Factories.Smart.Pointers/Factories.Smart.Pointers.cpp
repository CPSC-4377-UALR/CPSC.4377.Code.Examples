/*
* File: main.cpp
* Author: Keith Bush (2013)
*
* Purpose: Demonstrates an advanced use of the object factory design pattern
*   an extensible mechanism for allowing objects to be added via the ModLibrary class hook-in
*   which facilitates minimal recompilation of the code.
*/

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <string>
#include <memory>

#include"Library.h"
#include"BaseLibrary.h"
#include"ModLibrary.h"

int main() {

	int N = 10;

	//Factory types
	std::unique_ptr<Library> baseLibrary(std::make_unique<BaseLibrary>()); //storeas an inventory of base ObjectFactories
	std::unique_ptr<Library> modLibrary(std::make_unique<ModLibrary>());  //stores inventory of modifed ObjectFactories (if they exist)

																   //Imagine that the game is dynamically calling for types
	string objectType;

	//Display utility of the object factory
	std::vector<std::unique_ptr<Object>> objects;
	

	for (int i = 0; i<N; i++) {

		/*Randomly demand one of two types of object*/
		int tmp = rand() % 3 + 1;
		switch (tmp) {
		case 1:
			objectType = "child1";
			break;
		case 2:
			objectType = "child2";
			break;
		case 3:
			objectType = "child3";
			break;
		}

		cout << "TYPE: " << objectType << endl;
		Object* newObject=nullptr;

		//Search through the base classes
		if (baseLibrary->inventory.find(objectType) != baseLibrary->inventory.end()) {
			newObject = ((*(baseLibrary->inventory.find(objectType))).second)->create();
		}

		//Search through the mod classes
		if (modLibrary->inventory.find(objectType) != modLibrary->inventory.end()) {
			newObject = ((*(modLibrary->inventory.find(objectType))).second)->create();
		}

		//Load the resultant object into the game space
		if (newObject != nullptr) {
			objects.push_back(std::make_unique<Object>(newObject));
		}

	}

	//Display the game space
	std::vector<std::unique_ptr<Object>>::iterator objectsIter;
	for (objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++) {
		cout << (*objectsIter)->getNumber() << endl;
	}

	system("PAUSE");

	return 0;
}
