#include "ParamSettings.h"

void ParamSettings::save(const char* pFilename){
	
	tinyxml2::XMLDocument doc;  
	
	

	tinyxml2::XMLComment * comment;
	std::string commentText;

	//Label the XML formatting
	doc.InsertFirstChild(doc.NewDeclaration());
 
	//Build the root node
	tinyxml2::XMLNode* root = doc.NewElement(name.c_str());
	doc.InsertEndChild(root);
	
	commentText = " Parameters for " + name + " ";
	
	comment = doc.NewComment(commentText.c_str());
	root->LinkEndChild( comment );  

	std::map<std::string, Parameter>::iterator iter;

	//Form the node having children
	tinyxml2::XMLElement * params = doc.NewElement("Params");
	root->LinkEndChild( params );  //This links this node to the parent "SpaceShip" or "root" node  
 
	for(iter=paramMap.begin(); iter != paramMap.end(); iter++){
		
		//Grab the param (value) and param name (key)
		const std::string & key=(*iter).first;
		const PARAM_TYPE & type = (*iter).second.getType();
		const std::string & value = (*iter).second.getValue();

		//The key (parameter id) forms the node's name.  
		tinyxml2::XMLElement* param = doc.NewElement(key.c_str());

		//We can then mark-up each node's attributes 
		param->SetAttribute("type", type);
		param->SetAttribute("value", value.c_str());
		
		//Link this node to the parameter list
		params->LinkEndChild( param );  
	
	}

	doc.SaveFile(pFilename);  

}