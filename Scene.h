#pragma once
#include <string>
#include "Object.h"
#include "TileMapParser.h"
#include "KeyboardComponent.h"
#include "CollisionComponent.h"
#include "Debugger.h"
#include "Gravity.h"
#include "Quadtree.h"
#include "View.h"

class Scene
{
	std::unique_ptr<View> view;
	Gravity gravity;
	KeyboardMenager menager;
	std::vector<std::shared_ptr<Object>> objects;
	std::unique_ptr<mp::TileMapParser> parser;
	sf::Clock clock;
	sf::RenderWindow window;
	std::shared_ptr<CollisionComponent> myHero;
	std::vector<std::shared_ptr<CollisionComponent>> movable; // not this way, just to check if collision detection works
	Quadtree collidable;
	void draw();
	void collisionUpdate();
public:
	Scene(std::string sceneSourceName, sf::Vector2i resolution);
	Debugger debugger;
	void addObject(std::shared_ptr<Object> toAdd);
	const std::vector<std::shared_ptr<Object>>& getObjects() { return objects; }
	bool update();
	virtual ~Scene() {}
	void addCollidable(std::shared_ptr<CollisionComponent> toAdd);
};

