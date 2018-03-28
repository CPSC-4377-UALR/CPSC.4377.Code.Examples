#include "ParamSettings.h"

using namespace std;

int main(void){
	
	ParamSettings settings;
	settings.name = "SpaceShip";
	settings.paramMap["SPRITEPATH"] = Parameter("SpritePath", REQUIRED, "./Images/PaperPlayer.png");
	settings.paramMap["XPOS"] = Parameter("XPOS", REQUIRED, "14.7");
	settings.paramMap["YPOS"] = Parameter("YPOS", REQUIRED, "31.8");
	settings.paramMap["ANGLE"] = Parameter("ANGLE", OPTIONAL, "0.0f");
	settings.paramMap["FUEL"] = Parameter("FUEL", REQUIRED, "10");

	settings.save("./settings.xml");
	
}
