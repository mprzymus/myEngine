#pragma once
#include "CollisionComponent.h"
class CollisionResolver
{
protected:
	CollisionComponent* owner;
public:
	virtual ~CollisionResolver() {}
	virtual void resolveCollision(CollisionComponent& another) = 0;
	virtual void collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type) = 0;
	virtual void onBoundsAnswer(CollisionComponent& another) = 0;
	virtual void setOwner(CollisionComponent& Owner) { owner = &Owner; }
};

