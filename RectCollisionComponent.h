#pragma once
#include <SFML/Graphics/Rect.hpp>
#include "CollisionComponent.h"
#include "CollisionResolver.h"

class RectCollisionComponent :
	public CollisionComponent
{
	std::unique_ptr<CollisionResolver> resolver;
	sf::FloatRect bounds;
public:
	RectCollisionComponent(std::shared_ptr<Object> owner, std::unique_ptr<CollisionResolver> Resolver);
	void setOwner(std::shared_ptr<Object> owner) override;
	void update(float timeEllapsed) override;
	virtual bool isCollidng(const CollisionComponent& another) const override;
	const sf::FloatRect& getBounds() override { return bounds; }
	sf::Vector2f getCentre() const override;
	virtual void resolveCollision(CollisionComponent& another) override;
	virtual void collisionAnswer(CollisionComponent& another, CollisionComponent::CollisionType type) override;
	virtual void onBoundsAnswer(CollisionComponent& another) override;
	virtual float getHeight() const override { return bounds.height; }
	virtual float getWidth() const override { return bounds.width; }
	virtual float getLeft() const override { return bounds.left; }
	virtual float getTop() const override { return bounds.top; }
	bool operator== (const RectCollisionComponent& right) const;
};

