#pragma once
#include <SFML/System/Vector2.hpp>
#include "Component.h"

class PositionComponent : public Component
{
protected:
	sf::Vector2f position;
public:
	virtual void update(float timeElapsed)  override;
	PositionComponent(std::shared_ptr<Object> owner, sf::Vector2f position);
	virtual const sf::Vector2f& getPosition() const { return position; }
/*	virtual void move(sf::Vector2f toMove);
	virtual void setSpeed(sf::Vector2f speed);
	virtual void setCurrentSpeedX(float x);
	virtual void setCurrentSpeedY(float y);
	virtual void setCurrentSpeed(sf::Vector2f& speed);//sets current speed
	virtual const sf::Vector2f& getCurrentSpeed() const { return currentSpeed; }
	virtual const sf::Vector2f& getSpeed() const { return speed; }
	virtual void moveX(float distance);
	virtual void moveY(float distance);
	virtual void moveX(int distance);
	virtual void moveY(int distance);*/
};

