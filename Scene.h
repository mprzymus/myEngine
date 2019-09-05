#pragma once
#include <string>
#include "Object.h"
#include "TileMapParser.h"
#include "KeyboardComponent.h"
#include "CollisionComponent.h"
#include "Debugger.h"
#include "Gravity.h"

class Scene
{
	Gravity gravity;
	Debugger debugger;
	KeyboardMenager menager;
	std::vector<std::shared_ptr<Object>> objects;
	std::unique_ptr<mp::TileMapParser> parser;
	sf::Clock clock;
	sf::RenderWindow window;
	std::shared_ptr<CollisionComponent> myHero;
	std::vector<std::shared_ptr<CollisionComponent>> tempCollidableCollection; // not this way, just to check if collision detection works
public:
	void addObject(std::shared_ptr<Object> toAdd);
	Scene(std::string sceneSourceName);
	const std::vector<std::shared_ptr<Object>>& getObjects() { return objects; }
	bool update();
	virtual ~Scene() {}
	void addCollidable(std::shared_ptr<CollisionComponent> toAdd) { tempCollidableCollection.push_back(toAdd); }

};

