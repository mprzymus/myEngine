#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class GraphicComponent : public Component
{
	std::shared_ptr<sf::Texture> texture;
public:
	virtual void update(float) override;
	GraphicComponent(Object& owner, std::shared_ptr<sf::Texture> texture,
		sf::Vector2i texturePos,  float scale=1.f);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;
};

