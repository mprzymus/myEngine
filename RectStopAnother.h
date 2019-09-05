#pragma once
#include "CollisionResolver.h"
class RectStopAnother :
	public CollisionResolver
{
	virtual void resolveCollision(CollisionComponent& another) override;
};

