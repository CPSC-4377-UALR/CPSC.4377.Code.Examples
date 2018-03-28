#include "ParamSettings.h"

void ParamSettings::save(const char* pFilename){

	TiXmlDocument doc;  
	TiXmlComment * comment;
	std::string commentText;

	//Label the XML formatting
 	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl ); 
 
	//Build the root node
	TiXmlElement * root = new TiXmlElement(name.c_str());  
	doc.LinkEndChild( root );  

	comment = new TiXmlComment();
	commentText=" Parameters for "+ name + " ";
	comment->SetValue(commentText.c_str());  
	root->LinkEndChild( comment );  

	std::map<std::string, Parameter>::iterator iter;

	//Form the node having children
	TiXmlElement * params = new TiXmlElement( "Params" ); 
	root->LinkEndChild( params );  //This links this node to the parent "SpaceShip" or "root" node  
 
	for(iter=paramMap.begin(); iter != paramMap.end(); iter++){
		
		//Grab the param (value) and param name (key)
		const std::string & key=(*iter).first;
		const PARAM_TYPE & type = (*iter).second.getType();
		const std::string & value = (*iter).second.getValue();

		//The key (parameter id) forms the node's name.  
		TiXmlElement* param = new TiXmlElement(key.c_str());  

		//We can then mark-up each node's attributes 
		param->SetAttribute("type", type);
		param->SetAttribute("value", value.c_str());
		
		//Link this node to the parameter list
		params->LinkEndChild( param );  
	
	}

	doc.SaveFile(pFilename);  

}