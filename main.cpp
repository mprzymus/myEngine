#include "Game.h"

int main()
{
	Game myGame;
	while (myGame.isRunning())
	{
		myGame.update();
	}
	return 0;
}