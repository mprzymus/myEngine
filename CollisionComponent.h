#pragma once
#include "Component.h"
#include <SFML/System/Vector2.hpp>
class CollisionComponent :
	public Component
{
public:
	void update(float timeEllapsed) override {};
	virtual bool isCollidng(const CollisionComponent& another) const = 0;
	virtual void resolveCollision(CollisionComponent& another) = 0;
	virtual ~CollisionComponent() {};
	Object& getOwner() { return *owner; }
	virtual void setOwner(Object& owner) { this->owner = &owner; }
	virtual sf::Vector2f getCentre() const = 0;
	virtual float getHeight() const = 0;
	virtual float getWidth() const = 0;
	virtual float getLeft() const = 0;
	virtual float getTop() const = 0;
};

