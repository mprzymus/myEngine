#pragma once
#include "CollisionResolver.h"
class RectStopAnother :
	public CollisionResolver
{
	virtual void resolveCollision(CollisionComponent& another) override;
	virtual void collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type) override {}
};

