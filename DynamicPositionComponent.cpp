#include "DynamicPositionComponent.h"

DynamicPositionComponent::DynamicPositionComponent(std::shared_ptr<Object> owner, sf::Vector2f position, sf::Vector2f speed,
	sf::Vector2f currentSpeed) : PositionComponent(owner,position), currentSpeed(currentSpeed), speed(speed)
{}

void DynamicPositionComponent::update(float timeElapsed)
{
	position.x += timeElapsed * currentSpeed.x;
	position.y += timeElapsed * currentSpeed.y;
	currentSpeed.x = 0;
}

void DynamicPositionComponent::move(sf::Vector2f toMove)
{
	currentSpeed += toMove;
}

void DynamicPositionComponent::setSpeed(sf::Vector2f speed)
{
	this->speed = speed;
}

void DynamicPositionComponent::setCurrentSpeedX(float x)
{
	currentSpeed.x = x;
}

void DynamicPositionComponent::setCurrentSpeedY(float y)
{
	currentSpeed.y = y;
}

void DynamicPositionComponent::setCurrentSpeed(sf::Vector2f& speed)
{
	this->currentSpeed = speed;
}

void DynamicPositionComponent::moveX(float distance)
{
	position.x += distance;
}

void DynamicPositionComponent::moveY(float distance)
{
	position.y += distance;
}

void DynamicPositionComponent::moveX(int distance)
{
	position.x += distance;
}

void DynamicPositionComponent::moveY(int distance)
{
	position.y += distance;
}

void DynamicPositionComponent::setInAir(bool InAir)
{
	inAir = InAir;
}
