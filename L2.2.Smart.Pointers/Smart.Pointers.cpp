#include <iostream>
#include <memory>

int main()
{
//creating a shared pointer
	std::shared_ptr<int> i(new int);//bad
	std::shared_ptr<int> j(std::make_shared<int>);

	*i = 5;
	*j = 7;

	i = j; //the memory holding '7' is deleted here!
	return 0;
}