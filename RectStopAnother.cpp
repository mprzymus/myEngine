#include <algorithm>
#include <SFML\System\Vector2.hpp>
#include "RectStopAnother.h"
#include "Object.h"
#include <iostream>

void RectStopAnother::resolveCollision(CollisionComponent& another)
{
	if (!owner->isCollidng(another)) return;

	float xLeftDifference = owner->getCentre().x + owner->getWidth() / 2
		- another.getCentre().x + another.getWidth() / 2;
	float xRightDifference = owner->getCentre().x - owner->getWidth() / 2
		- another.getCentre().x - another.getWidth() / 2;
	float yUpDifference = owner->getCentre().y - owner->getHeight() / 2
		- another.getCentre().y - another.getHeight() / 2;
	float yDownDifference = owner->getCentre().y + owner->getHeight() / 2
		- another.getCentre().y + another.getHeight() / 2;

	float x = std::min(std::fabsf(xLeftDifference), std::fabsf(xRightDifference));
	float y = std::min(std::fabsf(yUpDifference), std::fabsf(yDownDifference));

	sf::Vector2f speed{ another.getOwner().getPosition().getCurrentSpeed() };

	if (x < y)
	{
		if (std::fabsf(xLeftDifference) < std::fabsf(xRightDifference))
		{
			//speed.x = std::max(speed.x, 0.f);
			another.getOwner().getPosition().moveX(xLeftDifference);
			//another.getOwner().getPosition().setCurrentSpeed(speed);
		}
		else
			another.getOwner().getPosition().moveX(xRightDifference);
	}
	else
	{
		if (std::fabsf(yUpDifference) < std::fabsf(yDownDifference))
			another.getOwner().getPosition().moveY(yUpDifference);
		else
			another.getOwner().getPosition().moveY(yDownDifference);
	}
	
}
