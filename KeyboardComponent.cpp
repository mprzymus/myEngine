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
			toMove.x += position->getSpeed().x;
			position->move(toMove);
			break;
		case KeyboardMenager::Left:
			toMove.x -= position->getSpeed().x;
			position->move(toMove);
			break;
		case KeyboardMenager::Jump:
			//toMove.y -= owner->getPosition().getSpeed().y;
			if (!position->isInAir())
			{
				toMove = { position->getCurrentSpeed().x, -position->getSpeed().y };
				position->setCurrentSpeed(toMove);
				position->setInAir(true);
				gravity.addObject(owner);
			}
			break;
		default:
			break;
		}
		x++;
	}
 	//owner->getPosition().move(toMove);
}
