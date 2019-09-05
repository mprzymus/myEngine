#include <SFML/Graphics.hpp>
#include <iostream>
#include "Debugger.h"
#include "Object.h"

void Debugger::addCollidable(std::shared_ptr<RectCollisionComponent> collidable)
{
	components.push_back(posData(collidable,collidable->getOwner().getPosition().getPosition()));
}

void Debugger::drawCollidableSquares()
{
	for (auto& collidable : components)
	{
		sf::VertexArray square(sf::LineStrip, 5);
		
		square[0].position = square[4].position = sf::Vector2f(collidable.first->getBounds().left, collidable.first->getBounds().top);
		square[1].position = sf::Vector2f(collidable.first->getBounds().left+collidable.first->getBounds().width, collidable.first->getBounds().top);
		square[2].position = sf::Vector2f(collidable.first->getBounds().left+collidable.first->getBounds().width, collidable.first->getBounds().top + collidable.first->getBounds().height);
		square[3].position = sf::Vector2f(collidable.first->getBounds().left, collidable.first->getBounds().top + collidable.first->getBounds().height);
		window.draw(square);
		sf::VertexArray centre(sf::Points, 1);
		centre[0].position = { collidable.first->getCentre().x, collidable.first->getCentre().y };
		window.draw(centre);

		if (loud && collidable.first->getOwner().getPosition().getPosition() != collidable.second)
			std::cout << "Was:" << collidable.second.x << ", " << collidable.second.y << " is: "
			<< collidable.first->getOwner().getPosition().getPosition().x << ", " 
			<< collidable.first->getOwner().getPosition().getPosition().y << std::endl;
		collidable.second = collidable.first->getOwner().getPosition().getPosition();
	}
}
