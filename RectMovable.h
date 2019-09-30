#pragma once
#include "CollisionResolver.h"
#include "Gravity.h"
class RectMovable :
	public CollisionResolver
{
	Gravity& gravity;
public:
	RectMovable(Gravity& gravity) : gravity(gravity) {}
	virtual void resolveCollision(CollisionComponent& another) override;
	virtual void collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type) override;
};

