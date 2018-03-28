#ifndef BASELIBRARY_H
#define BASELIBRARY_H

#include"Library.h"
#include"Child1Factory.h"
#include"Child2Factory.h"

using namespace std;

class BaseLibrary: public Library{

public:
	BaseLibrary() {
		inventory["child1"] = make_shared<Child1Factory>();
		inventory["child2"] = make_shared<Child2Factory>();
	}
};

#endif