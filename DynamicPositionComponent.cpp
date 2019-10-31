#include "DynamicPositionComponent.h"
#include <iostream>

DynamicPositionComponent::DynamicPositionComponent(std::shared_ptr<Object> owner, sf::Vector2f position, Gravity& gravity,
	sf::Vector2f speed, sf::Vector2f currentSpeed) : PositionComponent(owner, position), gravity(gravity), currentSpeed(currentSpeed),
	speed(speed), inAir(true), startedToFall(false) {
	std::cout << "here\n";
}

void DynamicPositionComponent::update(float timeElapsed)
{
	if (!inAir && startedToFall)
	{
		//std::cout << "Started to fall\n";
		gravity.addObject(owner);
		inAir = true;
	}
	position.x += timeElapsed * currentSpeed.x;
	position.y += timeElapsed * currentSpeed.y;
	currentSpeed.x = 0;
	startedToFall = true;
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
