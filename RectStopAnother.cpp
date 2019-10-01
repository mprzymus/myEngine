#include <algorithm>
#include <SFML\System\Vector2.hpp>
#include "RectStopAnother.h"
#include "Object.h"
#include "DynamicPositionComponent.h"
#include <iostream>

void RectStopAnother::resolveCollision(CollisionComponent& another)
{
	if (!owner->isCollidng(another))
	{
		//std::cout << "We do not collide\n";
		return;
	}
	auto position = dynamic_cast<DynamicPositionComponent*>(&another.getOwner()->getPosition());
	if (position == nullptr)
		return;
	CollisionComponent::CollisionType type;
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

	sf::Vector2f speed{ position->getCurrentSpeed() };

	//left or right
	if (x < y)
	{
		if (std::fabsf(xLeftDifference) < std::fabsf(xRightDifference))
		{
			type = CollisionComponent::CollisionType::left;
			//speed.x = std::max(speed.x, 0.f);
			position->moveX(xLeftDifference);
			//another.getOwner().getPosition().setCurrentSpeed(speed);
		}
		else
		{
			position->moveX(xRightDifference);
			type = CollisionComponent::CollisionType::right;
		}
	}
	else
	{
		//another is upper
		if (std::fabsf(yUpDifference) < std::fabsf(yDownDifference))
		{
			position->moveY(yUpDifference);
			type = CollisionComponent::CollisionType::up;
		}
		//another is lower
		else
		{
			position->moveY(yDownDifference);
			position->setCurrentSpeedY(std::fabsf(position->getCurrentSpeed().y));
			type = CollisionComponent::CollisionType::down;
		}
		another.collisionAnswer(*owner, type);
	}
	
}
