#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>

class GraphicComponent : public Component
{
	std::shared_ptr<sf::Texture> texture;
public:
	virtual void update(float) override;
	GraphicComponent(std::shared_ptr<Object> owner, std::shared_ptr<sf::Texture> texture,
		sf::Vector2i texturePos,  float scale = 1.f);
	GraphicComponent(std::shared_ptr<Object> owner, std::shared_ptr<sf::Texture> texture,
		sf::Vector2i texturePos, sf::Vector2i textureSize);
	void draw(sf::RenderWindow& window);
	sf::Sprite sprite;
};

