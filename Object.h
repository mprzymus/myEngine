#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "PositionComponent.h"
#include "GraphicComponent.h"

class Object
{
	std::unique_ptr<PositionComponent> position;
	std::unique_ptr<GraphicComponent> graphic;
	sf::Vector2i size; // have to move into any component, object shouldn't have to be rectangle
public:
	Object(sf::Vector2i size);
	void update(float timeElapsed);
	std::vector<std::shared_ptr<Component>> components;
	void setPosition(std::unique_ptr<PositionComponent> Position);
	void setGraphic(std::unique_ptr<GraphicComponent> Graphic);
	void addComponent(std::shared_ptr<Component> toAdd);
	void draw(sf::RenderWindow& widnow);
	const sf::Vector2i& getSize() { return size; }
	PositionComponent& getPosition() { return *position; }
	GraphicComponent& getGraphic() { return *graphic; }
};

