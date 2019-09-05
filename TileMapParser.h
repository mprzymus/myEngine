#pragma once
#include <SFML/System.hpp>
#include <vector>
#include <memory>
#include <string>
#include "pugixml.hpp"

namespace mp
{

struct TileData
{
	int x;
	int y;
	sf::Vector2i size;
	int tileId;
	bool isCollidable;
};

struct TextureData
{
	std::string path;
	int width;
	int height;
	int objectWidth;
	int objectHeight;
	std::string temp;
};

class TileMapParser
{
	std::vector<std::shared_ptr<TileData>> tiles;
	int tileWidth;
	int tileHeight;
	int mapHeight;
	int mapWidth;
	std::string mapFileName;
	std::string texturePath;
	TextureData texture;

	void makeTiles(const pugi::xml_node& node, const pugi::xml_node& collisionsNode);
	void textureSource(const std::string& fileName);

public:
	TileMapParser(const std::string& fileName);
	std::vector<std::shared_ptr<TileData>>& getTiles() { return tiles; }
	int getTileWidth() { return tileWidth; }
	int getTileHeight() { return tileHeight; }
	int getMapWidth() { return mapWidth; }
	int getMapHeight() { return mapHeight; }
	std::string& getTexturePath() { return texture.path; }
	std::string& getMapFileName() { return mapFileName; }
	const TextureData& getTextureData() { return texture; }
};
}

