#pragma once
#include <vector>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "Component.h"
#include "PositionComponent.h"
#include "GraphicComponent.h"
#include"IdComponent.h"

class Object
{
	std::unique_ptr<PositionComponent> position;
	std::unique_ptr<GraphicComponent> graphic;
	sf::Vector2i size;
	std::vector<std::shared_ptr<Component>> components;
	IdComponent id;
public:
	Object(sf::Vector2i size);
	void update(float timeElapsed);
	void setPosition(std::unique_ptr<PositionComponent> Position);
	void setGraphic(std::unique_ptr<GraphicComponent> Graphic);
	void addComponent(std::shared_ptr<Component> toAdd);
	void draw(sf::RenderWindow& widnow);
	const sf::Vector2i& getSize() { return size; }
	PositionComponent& getPosition() { return *position; }
	GraphicComponent& getGraphic() { return *graphic; }
	int getId() { return id.getId(); }
};

