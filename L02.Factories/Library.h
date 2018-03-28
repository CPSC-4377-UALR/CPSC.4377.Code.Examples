#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include<string>
#include<map>
#include"ObjectFactory.h"

using namespace std;

class Library {

public:
	map<string, ObjectFactory*> inventory;
};

#endif