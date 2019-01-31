#include <map>
#include <string>

#include "tinyxml2.h"


typedef enum{REQUIRED, RECOMMENDED, OPTIONAL} PARAM_TYPE;

class Parameter{
public:

	//Constructor
	Parameter(): name("Undefined"), type(OPTIONAL), value("NA"){}
	Parameter(std::string name, PARAM_TYPE type, std::string value){

		//Set parameter type
		this->name = name;
		this->type = type;
		this->value = value;

	}

	std::string name;
	PARAM_TYPE type;
	std::string value;

	//Getters
	std::string getName(){return(name);}
	PARAM_TYPE getType(){return(type);}
	std::string getValue(){return(value);}

};



// a basic window abstraction - demo purposes only
class ParamSettings{
public:

	//Constructor and public methods
	ParamSettings(): name("unknown"), type("OBJECT"){}
	void save(const char* pFilename);
	//void load(const char* pFilename); //Not yet implemented

	//Note: should be private/protected but public for learning purposes
	std::string name;
	std::string type;
	std::map<std::string, Parameter> paramMap;

};

