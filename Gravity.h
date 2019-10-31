#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "Object.h"

class Gravity
{
	const float g; // gravitational acceleration
	std::vector<Object*> entities;
public:
	Gravity(const float gravitational_acceleration = 9.81) : g(gravitational_acceleration) {}
	const std::vector<Object*>& getObjects() { return entities; }
	void addObject(Object* toAdd);
	bool removeObject(Object* toRemove);
	void update(float timeElapsed);
};

