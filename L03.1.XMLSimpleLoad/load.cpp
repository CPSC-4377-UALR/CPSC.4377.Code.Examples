#include <iostream>

#include "tinystr.h"
#include "tinyxml.h"

void main(){

    
    //Parse XML file
	TiXmlDocument doc("load.xml");
    doc.LoadFile();


    //Get handle
    TiXmlHandle hDoc(&doc);

    //Get root
    TiXmlElement* root = nullptr;
	root = doc.FirstChildElement("Object");
    if(!root){
        std::cout << "Error" << std::endl;
	}

    //Extract Numeric Attribute
    float value;
    root->QueryFloatAttribute("value", &value);
	std::cout << value << std::endl;

    //Extract a string Attribute
    std::cout << root->Attribute("name") << std::endl;

    //Get the Child Element
    TiXmlElement* element = root->FirstChildElement("Data");

    //Extract a string Attribute
  	std::cout << element->Attribute("valuestr") << std::endl;

    //Get another Child Element
	element = element->NextSiblingElement("Data");

    //Extract a string Attribute
  	std::cout << element->Attribute("valuestr") << std::endl;

    system("PAUSE");

}

