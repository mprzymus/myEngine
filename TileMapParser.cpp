#include "TileMapParser.h"
#include <stdexcept>
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

using namespace mp;

TileMapParser::TileMapParser(const std::string & fileName) 
{
	pugi::xml_document doc;
	if (!doc.load_file(fileName.c_str())) 
		throw std::invalid_argument("no such directory for tmx file for this map");
	mapFileName = fileName;
	pugi::xml_node parentNode = doc.child("map");
	std::string tsxFile = parentNode.child("tileset").attribute("source").value();
	textureSource(tsxFile);
	tileWidth = parentNode.attribute("tilewidth").as_int();
	tileHeight = parentNode.attribute("tileheight").as_int();
	makeTiles(parentNode.find_child_by_attribute("layer","name", "Tiles"), 
		parentNode.find_child_by_attribute("layer", "name", "Collisions"));
}

void TileMapParser::makeTiles(const pugi::xml_node& tilesNode, 
	const pugi::xml_node& collisionsNode)
{
	mapHeight = tilesNode.attribute("height").as_int();
	mapWidth = tilesNode.attribute("width").as_int();
	auto mapDataNode = tilesNode.child("data");
	auto collisionsDataNode = collisionsNode.child("data");
	std::stringstream tileStream (mapDataNode.text().get());
	std::stringstream collisionStream(collisionsDataNode.text().get());
	int counter = 0;
	while (tileStream.good())
	{
		std::string number;
		std::string collision;
		std::getline(tileStream, number, ',');
		std::getline(collisionStream, collision, ',');
		
		int textureId = std::stoi(number);
		bool isCollisable = std::stoi(collision); // TODO find way to do this without casting int into bool
		if (textureId != 0)
		{
			std::shared_ptr<TileData> newTile = std::make_shared<TileData>();
			newTile->x = counter % mapWidth;
			newTile->y = counter / mapWidth;
			newTile->size = { tileWidth,tileHeight };
			newTile->tileId = textureId-1;
			newTile->isCollidable = isCollisable;
			tiles.push_back(newTile);
		}
		else if (isCollisable)
			throw std::invalid_argument("File unsupported. Only tiles can be collidable");
		counter++;
	}
}

void TileMapParser::textureSource(const std::string& fileName)
{
	pugi::xml_document doc;
	if (!doc.load_file(fileName.c_str()))
	{
		std::string message = "no \"" + fileName + "\" directory for tsx file of this map";
		throw std::invalid_argument(message);
	}
	pugi::xml_node node = doc.child("tileset");
	node = node.child("image");
	texture.path = node.attribute("source").value();
	texture.height = node.attribute("height").as_int();
	texture.width = node.attribute("width").as_int();
	node = node.parent().child("tile").child("objectgroup").child("object");
	texture.objectHeight = node.attribute("height").as_int();
	texture.objectWidth = node.attribute("width").as_int();
	texture.height = texture.height / texture.objectHeight;
	texture.width = texture.width / texture.objectWidth;
}
