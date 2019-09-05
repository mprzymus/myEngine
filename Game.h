#pragma once
#include "Scene.h"
#include "SceneMachine.h"

class Game
{
	bool running;
	const int scenesAmount=1;//in futere to read from file
	std::vector<std::unique_ptr<Scene>> scenes;
	std::unique_ptr<Scene> currentScene;
	sf::Clock fpsTimer;
	int fps;
public:
	bool isRunning();
	void setRunning(bool isRunning);
	Game();
	void update();
};
