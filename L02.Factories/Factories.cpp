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
#include <random>

#include"Library.h"
#include"BaseLibrary.h"
#include"ModLibrary.h"

using namespace std;

int main() {

	int N = 10;

	//Factory types
	Library* baseLibrary = (Library*)new BaseLibrary(); //storeas an inventory of base ObjectFactories
	Library* modLibrary = (Library*)new ModLibrary();  //stores inventory of modifed ObjectFactories (if they exist)

																   //Imagine that the game is dynamically calling for types
	string objectType;

	//Display utility of the object factory
	vector<Object*> objects;
	

	for (int i = 0; i<N; i++) {

		/*Randomly demand one of two types of object*/
		static random_device seed;
		static default_random_engine e(seed());
		static uniform_int_distribution<int> randomChild(1, 3);
		switch (randomChild(e)) {
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

		//C++ 17 version
		//if (auto libraryPair = baseLibrary->inventory.find(objectType); libraryPair != baseLibrary->inventory.end())
		//{
		//	auto[name, factory] = *libraryPair; // <string, ObjectFactory*>

		//	cout << name << endl;
		//	newObject = factory->create();
		//}
		//if (auto libraryPair = modLibrary->inventory.find(objectType); libraryPair != modLibrary->inventory.end())
		//{
		//	auto[name, factory] = *libraryPair;
		//	cout << name;
		//	newObject = factory->create();
		//}

		//Load the resultant object into the game space
		if (newObject != nullptr) {
			objects.push_back(newObject);
		}

		

	}

	//Display the game space
	vector<Object*>::iterator objectsIter;
	for (objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++) {
		cout << (*objectsIter)->getNumber() << endl;
	}

	for (objectsIter = objects.begin(); objectsIter != objects.end(); objectsIter++) {
		delete (*objectsIter);
	}

	system("PAUSE");

	return 0;
}
