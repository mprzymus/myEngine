#include "Object.h"

Object::Object(sf::Vector2i size) : id(this)
{
	this->size = size;
}

void Object::update(float timeElapsed)
{
	for (auto& component : components)
		component->update(timeElapsed);
	position->update(timeElapsed);
	graphic->update(timeElapsed);
}

void Object::setPosition(std::unique_ptr<PositionComponent> Position)
{
	position = std::move(Position);
}

void Object::setGraphic(std::unique_ptr<GraphicComponent> Graphic)
{
	graphic = std::move(Graphic);
}

void Object::addComponent(std::shared_ptr<Component> toAdd)
{
	components.push_back(toAdd);
}

void Object::draw(sf::RenderWindow& widnow)
{
	graphic->draw(widnow);
}
