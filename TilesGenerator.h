#pragma once
#include "TileMapParser.h"
#include "Scene.h"
#include "CollisionComponent.h"

namespace mp
{
	class TilesGenerator
	{
		std::shared_ptr<mp::TileMapParser> parser = nullptr;
		sf::Vector2i countTexturePosition(mp::TileMapParser& parser, mp::TileData& element);
		std::shared_ptr<CollisionComponent>generateCollidable(TileData& element, Object& object);
	public:
		TilesGenerator() {}
		TilesGenerator(std::string sourceName);
		TilesGenerator(std::shared_ptr<mp::TileMapParser> Parser);
		void generate(Scene& sceneForObjects);
	};
}
