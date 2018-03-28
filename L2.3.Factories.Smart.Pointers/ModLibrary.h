#ifndef MODGAMEFACTORY_H
#define MODGAMEFACTORY_H

#include "Library.h"
#include"Child3Factory.h"



class ModLibrary : public Library {

public:

	ModLibrary() {
		inventory["child3"] = make_shared<Child3Factory>();
	}
};

#endif