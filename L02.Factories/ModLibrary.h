#ifndef MODGAMEFACTORY_H
#define MODGAMEFACTORY_H

#include "Library.h"
#include"Child3Factory.h"



class ModLibrary : Library {

public:

	ModLibrary() {
		inventory["child3"] = (ObjectFactory*)new Child3Factory();
	}
};

#endif