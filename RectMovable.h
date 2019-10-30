#pragma once
#include "CollisionResolver.h"
#include "Gravity.h"
#include "DynamicPositionComponent.h"
class RectMovable :
	public CollisionResolver
{
	Gravity& gravity;
	DynamicPositionComponent* position;
public:
	RectMovable(Gravity& gravity);
	virtual void resolveCollision(CollisionComponent& another) override;
	virtual void collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type) override;
	virtual void onBoundsAnswer(CollisionComponent& another) override;
	virtual void setOwner(CollisionComponent& Owner) override;
};

