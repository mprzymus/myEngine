#include "PositionComponent.h"
#include "Object.h"
#include <iostream>
#include <cmath>

void PositionComponent::update(float timeElapsed)
{
	position.x += timeElapsed * currentSpeed.x;
	position.y += timeElapsed * currentSpeed.y;
	currentSpeed.x = 0;
	//currentSpeed.y = 0;
}

PositionComponent::PositionComponent(Object& owner, sf::Vector2f position, sf::Vector2f speed,
	sf::Vector2f currentSpeed) : currentSpeed(currentSpeed)
{
	this->speed = speed;
	this->position = position;
	this->owner = &owner; 
}

void PositionComponent::move(sf::Vector2f toMove)
{
	currentSpeed += toMove;
}

void PositionComponent::setSpeed(sf::Vector2f speed)
{
	this->speed = speed;
}

void PositionComponent::setCurrentSpeed(sf::Vector2f& speed)
{
	this->currentSpeed = speed;
}

void PositionComponent::moveX(float distance)
{
	position.x += distance;
}

void PositionComponent::moveY(float distance)
{
	position.y += distance;
}

void PositionComponent::moveX(int distance)
{
	position.x += distance;
}

void PositionComponent::moveY(int distance)
{
	position.y += distance;
}
