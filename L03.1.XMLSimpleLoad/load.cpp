#include <iostream>

#include "tinyxml2.h"

void main(){

	tinyxml2::XMLDocument doc;
    
	if (doc.LoadFile("load.xml") != tinyxml2::XML_SUCCESS)
	{
		printf("Bad File Path");
		exit(1);
	}


    //Get root
	tinyxml2::XMLElement* root= doc.FirstChildElement("Object");
    
	if(!root){
        printf("Error");
	}

    //Extract Numeric Attribute
    float value;
	root->QueryFloatAttribute("value", &value);
	std::cout << value << std::endl;

    //Extract a string Attribute
    std::cout << root->Attribute("name") << std::endl;

    //Get the Child Element
	tinyxml2::XMLElement* element = root->FirstChildElement("Data");

    //Extract a string Attribute
  	std::cout << element->Attribute("valuestr") << std::endl;

    //Get another Child Element
	element = element->NextSiblingElement("Data");

    //Extract a string Attribute
  	std::cout << element->Attribute("valuestr") << std::endl;

    system("PAUSE");

}

