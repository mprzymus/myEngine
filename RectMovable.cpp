#include <cmath>
#include <algorithm>
#include "RectMovable.h"
#include "Object.h"

void RectMovable::resolveCollision(CollisionComponent& another)
{
	if (!owner->isCollidng(another))
	{
		//std::cout << "We do not collide\n";
		return;
	}
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

	sf::Vector2f speed{ another.getOwner()->getPosition().getCurrentSpeed() };

	//left or right
	if (x < y)
	{
		if (std::fabsf(xLeftDifference) < std::fabsf(xRightDifference))
		{
			type = CollisionComponent::CollisionType::left;
			//speed.x = std::max(speed.x, 0.f);
			another.getOwner()->getPosition().moveX(xLeftDifference);
			//another.getOwner().getPosition().setCurrentSpeed(speed);
		}
		else
		{
			another.getOwner()->getPosition().moveX(xRightDifference);
			type = CollisionComponent::CollisionType::right;
		}
	}
	else
	{
		//another is upper
		if (std::fabsf(yUpDifference) < std::fabsf(yDownDifference))
		{
			another.getOwner()->getPosition().moveY(yUpDifference);
			type = CollisionComponent::CollisionType::up;
		}
		//another is lower
		else
		{
			auto& pos = another.getOwner()->getPosition();
			pos.moveY(yDownDifference);
			pos.setCurrentSpeedY(std::fabsf(pos.getCurrentSpeed().y));
			type = CollisionComponent::CollisionType::down;
		}
		another.collisionAnswer(*owner, type);
	}
}

void RectMovable::collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type)
{
	if (type == CollisionComponent::CollisionType::up)
	{
		gravity.removeObject(owner->getOwner());
		owner->getOwner()->getPosition().setCurrentSpeedY(0.f);
	}
}
