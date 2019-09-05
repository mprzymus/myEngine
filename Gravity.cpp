#include "Gravity.h"
#include "SFML/System/Vector2.hpp"
#include <iostream>
#include <ctime>
#include <cmath>
#include <climits>
#include <algorithm>

/*Ground::Ground(const sf::Shape& shape, std::vector<Movable*>& objects, const float gravitational_acceleration)
	: ground(shape), entities(objects), g(gravitational_acceleration/pow(10.f,12.f)*45.f)
{}

Ground::Ground(const sf::Shape& shape, const float gravitational_acceleration)
	: ground(shape), g(gravitational_acceleration/ pow(10.f, 12.f)*45.f)
{}*/

void Gravity::addObject(std::shared_ptr<Object> toAdd)
{
	entities.push_back(toAdd);
}

bool Gravity::removeObject(std::shared_ptr<Object> toRemove)
{
	auto it = std::find(entities.begin(), entities.end(), toRemove);
	if (it != entities.end())
	{
		entities.erase(it);
		return true;
	}
	return false;
}

void Gravity::update(float timeElapsed)
{
	sf::Vector2f speedToAdd = { 0.f, timeElapsed * g };
	for (auto & object : entities)
	{
		object->getPosition().move(speedToAdd);
		//std::cout << object->getPosition().getCurrentSpeed().y << std::endl;
	}
}
