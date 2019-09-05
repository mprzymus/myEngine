#pragma once
#include "CollisionComponent.h"
class CollisionResolver
{
protected:
	CollisionComponent* owner;
public:
	virtual void resolveCollision(CollisionComponent& another) = 0;
	virtual void setOwner(CollisionComponent& Owner) { owner = &Owner; }
};

