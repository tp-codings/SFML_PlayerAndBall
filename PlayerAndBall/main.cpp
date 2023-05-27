#include "Engine.h"

using namespace sf;

int main()
{
	//Initilize random seed
	srand(static_cast<unsigned>(time(0)));


	//Initilize Game Object
	Engine Engine;

	//Game Loop
	while (Engine.running())
	{
		Engine.update();
		Engine.render();
	}

	//End of Game

	return 0;
}