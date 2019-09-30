#include "KeyboardComponent.h"
#include "Object.h"
#include <iostream>

void KeyboardComponent::update(float timeElapsed)
{
	sf::Vector2f toMove{ 0,0 };
	const std::vector<KeyboardMenager::input>& input = menager.currentInput();
	int x = 0;
	auto owner = this->owner.lock();
	while (input.size() > x)
	{
		switch (input.at(x))
		{
		case KeyboardMenager::Right:
			toMove.x += owner->getPosition().getSpeed().x;
			owner->getPosition().move(toMove);
			break;
		case KeyboardMenager::Left:
			toMove.x -= owner->getPosition().getSpeed().x;
			owner->getPosition().move(toMove);
			break;
		case KeyboardMenager::Jump:
			//toMove.y -= owner->getPosition().getSpeed().y;
			toMove = { owner->getPosition().getCurrentSpeed().x, -owner->getPosition().getSpeed().y };
			owner->getPosition().setCurrentSpeed(toMove);
			break;
		default:
			break;
		}
		x++;
	}
 	//owner->getPosition().move(toMove);
}
