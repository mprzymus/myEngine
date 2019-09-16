#include "TilesGenerator.h"
#include "GraphicComponent.h"
#include <SFML/Graphics.hpp>
#include <exception>
#include "RectCollisionComponent.h"
#include "RectStopAnother.h"

using namespace mp;

TilesGenerator::TilesGenerator(std::string sourceName)
{
	parser = std::make_shared<mp::TileMapParser>(sourceName);
}

TilesGenerator::TilesGenerator(std::shared_ptr<mp::TileMapParser> Parser)
{
	parser = Parser;
}

void TilesGenerator::generate(Scene& sceneForObjects)
{
	std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
	if (!texture->loadFromFile(parser->getTextureData().path))
		throw std::invalid_argument("No such texture to load file for map.");
	sf::Vector2f speed = { 0.f,0.f };
	sf::Vector2i size{parser->getTileWidth(), parser->getTileHeight()};
	for (auto element : parser->getTiles())
	{
		sf::Vector2f position{(float)element->x * parser->getTileWidth(), 
			(float)element->y * parser->getTileHeight() };
		auto object = std::make_shared<Object>(size);
		std::unique_ptr<PositionComponent> pComponent = std::make_unique<PositionComponent>
			(*object, position, speed);
		object->setPosition(std::move(pComponent));
		sf::Vector2i onTex = countTexturePosition(*parser, *element);
		std::unique_ptr<GraphicComponent> gComponent =
			std::make_unique<GraphicComponent>(*object,texture,onTex);
		object->setGraphic(std::move(gComponent));
		sceneForObjects.addObject(object);
		if (element->isCollidable)
		{
			std::shared_ptr<CollisionComponent>collidable = generateCollidable(*element, *object);
			collidable->setOwner(*object);
			object->addComponent(collidable);
			sceneForObjects.addCollidable(collidable);

		}
	}
}

sf::Vector2i TilesGenerator::countTexturePosition(mp::TileMapParser& parser, mp::TileData& element)
{
	int line = element.tileId / parser.getTextureData().width * parser.getTextureData().objectHeight;
	int column = element.tileId % parser.getTextureData().width * parser.getTextureData().objectWidth;
	sf::Vector2i toReturn = {column, line};
	return toReturn;
}

std::shared_ptr<CollisionComponent> mp::TilesGenerator::generateCollidable(mp::TileData& element, Object& object)
{
	std::shared_ptr<CollisionComponent> toReturn = std::make_shared<RectCollisionComponent>(std::move(std::make_unique<RectStopAnother>()));
	return toReturn;
}
