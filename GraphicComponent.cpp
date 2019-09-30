#include "GraphicComponent.h"
#include "Object.h"

void GraphicComponent::update(float)
{
	sprite.setPosition(owner.lock()->getPosition().getPosition().x, owner.lock()->getPosition().getPosition().y);
}

GraphicComponent::GraphicComponent(std::shared_ptr<Object> owner, std::shared_ptr<sf::Texture> texture,
	sf::Vector2i texturePos, float scale)
{
	this->owner = owner;
	sprite.setPosition(owner->getPosition().getPosition().x, owner->getPosition().getPosition().y);
	sprite.setTexture(*texture);
	sprite.setTextureRect(sf::IntRect(texturePos, owner->getSize()));
	//sprite.setScale(scale, scale);
	this->texture = texture;
}

void GraphicComponent::draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
