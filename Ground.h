#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include "Object.h"

class Gravity
{
	const float g; // gravitational acceleration
	std::vector<std::shared_ptr<Object>> entities;
public:
	Gravity(const float gravitational_acceleration = 9.81) : g(gravitational_acceleration) {}
	std::vector<std::shared_ptr<Object>>& getObjects() { return entities; }
	void addObject(std::shared_ptr<Object> toAdd);
	bool removeObject(std::shared_ptr<Object> toRemove);
	void update(float timeElapsed);
};

