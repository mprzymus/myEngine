#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Object.h"

class View
{
	sf::View view;
	std::shared_ptr<Object> centralObject;
public:
	View(std::shared_ptr<Object> CentralObject, float width, float height);
	void update();
	const sf::View& getView() { return view; }
};

