#pragma once
#include <SFML/System/Vector2.hpp>
#include "Component.h"

class PositionComponent : public Component
{
	sf::Vector2f currentSpeed;
	sf::Vector2f position;
	sf::Vector2f speed; // TODO make it  private
public:
	virtual void update(float timeElapsed)  override;
	PositionComponent(Object& owner, sf::Vector2f position, sf::Vector2f speed,
		sf::Vector2f currentSpeed = { 0,0 });
	void move(sf::Vector2f toMove);
	void setSpeed(sf::Vector2f speed);
	void setCurrentSpeed(sf::Vector2f& speed);//sets current speed
	const sf::Vector2f& getCurrentSpeed() const { return currentSpeed; }
	const sf::Vector2f& getPosition() const { return position; }
	const sf::Vector2f& getSpeed() const { return speed; }
	void moveX(float distance);
	void moveY(float distance);
	void moveX(int distance);
	void moveY(int distance);
};

