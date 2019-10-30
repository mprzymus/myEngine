#include "Game.h"
#include <iostream>
#include <memory>
#include <array>

int main()
{
	Game myGame;
	while (myGame.isRunning())
	{
		myGame.update();
	}
	return 0;
}