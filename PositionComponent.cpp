#include "PositionComponent.h"
#include "Object.h"
#include <iostream>
#include <cmath>

void PositionComponent::update(float timeElapsed)
{}

PositionComponent::PositionComponent(std::shared_ptr<Object> owner, sf::Vector2f position) : Component(owner)
{
	this->position = position;
}