#include "RectCollisionComponent.h"
#include "Object.h"
#include <iostream>

RectCollisionComponent::RectCollisionComponent(std::unique_ptr<CollisionResolver> Resolver)
{
	resolver = std::move(Resolver);
	resolver->setOwner(*this);
}

void RectCollisionComponent::setOwner(Object& owner)
{
	this->owner = &owner;
	bounds.left = owner.getPosition().getPosition().x;
	bounds.top = owner.getPosition().getPosition().y;
	bounds.height = owner.getSize().y;
	bounds.width = owner.getSize().x;
}

void RectCollisionComponent::update(float timeEllapsed)
{
	bounds.top = owner->getPosition().getPosition().y;
	bounds.left = owner->getPosition().getPosition().x;
}

bool RectCollisionComponent::isCollidng(const CollisionComponent& another) const
{
	const RectCollisionComponent& rect = dynamic_cast<const RectCollisionComponent&>(another);
	return bounds.intersects(rect.bounds);
}

sf::Vector2f RectCollisionComponent::getCentre() const
{
	return sf::Vector2f(bounds.left + bounds.width/2, bounds.top + bounds.height/2);
}

void RectCollisionComponent::resolveCollision(CollisionComponent& another)
{
	resolver->resolveCollision(another);
	another.update(0.f);
}

bool RectCollisionComponent::operator==(const RectCollisionComponent& right) const
{
	return bounds == right.bounds;
}
