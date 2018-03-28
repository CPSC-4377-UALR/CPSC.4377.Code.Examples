#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include<string>
#include<map>
#include <memory>
#include"ObjectFactory.h"


using namespace std;

class Library {

public:
	map<string, shared_ptr<ObjectFactory>> inventory;
};

#endif