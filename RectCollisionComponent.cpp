#include "RectCollisionComponent.h"
#include "Object.h"
#include <iostream>

RectCollisionComponent::RectCollisionComponent(std::shared_ptr<Object> owner, std::unique_ptr<CollisionResolver> Resolver) : CollisionComponent(owner)
{
	resolver = std::move(Resolver);
}

void RectCollisionComponent::setOwner(std::shared_ptr<Object> owner)
{
	this->owner = owner.get();
	bounds.left = owner->getPosition().getPosition().x;
	bounds.top = owner->getPosition().getPosition().y;
	bounds.height = (float)owner->getSize().y;
	bounds.width = (float)owner->getSize().x;
	resolver->setOwner(*this);
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

void RectCollisionComponent::collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type)
{
	resolver->collisionAnswer(another, type);
}

void RectCollisionComponent::onBoundsAnswer(CollisionComponent& another)
{
	resolver->onBoundsAnswer(another);
}

bool RectCollisionComponent::operator==(const RectCollisionComponent& right) const
{
	return bounds == right.bounds;
}
