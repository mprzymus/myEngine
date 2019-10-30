#pragma once
#include "Gravity.h"
#include "PositionComponent.h"
class DynamicPositionComponent :
	public PositionComponent
{
	sf::Vector2f currentSpeed;
	sf::Vector2f speed;
	bool inAir;
	bool startedToFall;
	Gravity& gravity;
public:
	DynamicPositionComponent(std::shared_ptr<Object> owner, sf::Vector2f position, Gravity& gravity, sf::Vector2f speed,
		sf::Vector2f currentSpeed = { 0,0 });
	virtual void update(float timeElapsed)  override;
	const sf::Vector2f& getCurrentSpeed() const { return currentSpeed; }
	void move(sf::Vector2f toMove);
	void setSpeed(sf::Vector2f speed);
	void setCurrentSpeedX(float x);
	void setCurrentSpeedY(float y);
	void setCurrentSpeed(sf::Vector2f& speed);
	const sf::Vector2f& getSpeed() const { return speed; }
	void moveX(float distance);
	void moveY(float distance);
	void moveX(int distance);
	void moveY(int distance);
	bool isInAir() { return inAir; }
	void setInAir(bool InAir);
	void setStartedToFall(bool StartedToFall) { startedToFall = StartedToFall;  }
};