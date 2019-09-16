#pragma once
#include <vector>
#include "RectCollisionComponent.h"

using pairData = std::pair < std::shared_ptr<RectCollisionComponent>, sf::Vector2f>;

class Debugger
{
	struct posData
	{
		std::pair<std::shared_ptr<RectCollisionComponent>, sf::Vector2f> data;
		bool isSpecial;
		bool operator== (const posData& right)const { return data.first == right.data.first; }
		posData(pairData Data)
			: data(Data), isSpecial(false) {}
		std::shared_ptr<RectCollisionComponent>& first() { return data.first; }
		sf::Vector2f& second() { return data.second; }
	};
	bool loud;
	sf::RenderWindow& window;
	std::vector<posData> components;
public:
	Debugger(sf::RenderWindow& window, bool loud = false) : window(window), loud(loud) {}
	void addCollidable(std::shared_ptr<RectCollisionComponent> collidable);
	void removeCollidable(std::shared_ptr<RectCollisionComponent> collidable);
	void drawCollidableSquares();
	void setSpecial(std::shared_ptr<RectCollisionComponent> collidable, bool special);
};

