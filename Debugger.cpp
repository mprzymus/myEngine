#include <SFML/Graphics.hpp>
#include <iostream>
#include "Debugger.h"
#include "Object.h"

void Debugger::addCollidable(std::shared_ptr<RectCollisionComponent> collidable)
{
	posData temp(pairData(collidable, collidable->getOwner()->getPosition().getPosition()));
	components.push_back(temp);
}

void Debugger::removeCollidable(std::shared_ptr<RectCollisionComponent> collidable)
{
	auto it = std::find(components.begin(), components.end(), posData(pairData(collidable, collidable->getOwner()->getPosition().getPosition())));
	if (it != components.end())
		components.erase(it);
}

void Debugger::setSpecial(std::shared_ptr<RectCollisionComponent> collidable, bool special)
{
	auto it = std::find(components.begin(), components.end(), posData(pairData(collidable, collidable->getOwner()->getPosition().getPosition())));
	if (it != components.end())
		it->isSpecial = special;
}

void Debugger::drawCollidableSquares()
{
	for (auto& collidable : components)
	{
		sf::VertexArray square(sf::LineStrip, 5);
		sf::Color color;
		
		square[0].position = square[4].position = sf::Vector2f(collidable.first()->getBounds().left, collidable.first()->getBounds().top);
		square[1].position = sf::Vector2f(collidable.first()->getBounds().left+collidable.first()->getBounds().width, collidable.first()->getBounds().top);
		square[2].position = sf::Vector2f(collidable.first()->getBounds().left+collidable.first()->getBounds().width, collidable.first()->getBounds().top + collidable.first()->getBounds().height);
		square[3].position = sf::Vector2f(collidable.first()->getBounds().left, collidable.first()->getBounds().top + collidable.first()->getBounds().height);

		sf::VertexArray centre(sf::Points, 1);
		centre[0].position = { collidable.first()->getCentre().x, collidable.first()->getCentre().y };

		if (collidable.isSpecial) {
			for (int i = 0; i < 4; i++)
				square[i].color = sf::Color::Red;
			centre[0].color = sf::Color::Red;
			collidable.isSpecial = false;
		}
		window.draw(centre);
		window.draw(square);

		if (loud && collidable.first()->getOwner()->getPosition().getPosition() != collidable.second())
			std::cout << "Was:" << collidable.second().x << ", " << collidable.second().y << " is: "
			<< collidable.first()->getOwner()->getPosition().getPosition().x << ", " 
			<< collidable.first()->getOwner()->getPosition().getPosition().y << std::endl;
		collidable.second() = collidable.first()->getOwner()->getPosition().getPosition();
	}
}
