#ifndef BASELIBRARY_H
#define BASELIBRARY_H

#include"Library.h"
#include"Child1Factory.h"
#include"Child2Factory.h"

using namespace std;

class BaseLibrary: Library{

public:
	BaseLibrary() {
		inventory["child1"] = (ObjectFactory*)new Child1Factory();
		inventory["child2"] = (ObjectFactory*)new Child2Factory();
	}
};

#endif