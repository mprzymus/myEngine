#include "Game.h"
#include <iostream>

bool Game::isRunning()
{
	return running;
}

void Game::setRunning(bool isRunning)
{
	running = isRunning;
}

Game::Game() : running(true)
{
	fps = 0;
	currentScene = std::make_unique<Scene>("pierwsza mapa.tmx", sf::Vector2i(1920,1080));//one scene so far
	
}

void Game::update()
{
	fps++;
	running = currentScene->update();
	if (fpsTimer.getElapsedTime().asSeconds() >= 1.f)
	{
		std::cout << "fps: " << fps << std::endl;
		fpsTimer.restart();
		fps = 0;
	}
}
