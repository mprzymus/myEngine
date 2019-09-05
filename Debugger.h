#pragma once
#include <vector>
#include "RectCollisionComponent.h"

using posData = std::pair<std::shared_ptr<RectCollisionComponent>, sf::Vector2f>;

class Debugger
{
	bool loud;
	sf::RenderWindow& window;
	std::vector<posData> components;
public:
	Debugger(sf::RenderWindow& window, bool loud = false) : window(window), loud(loud) {}
	void addCollidable(std::shared_ptr<RectCollisionComponent> collidable);
	void drawCollidableSquares();
};

