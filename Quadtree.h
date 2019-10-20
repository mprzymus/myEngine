#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "CollisionComponent.h"

class Quadtree
{
	int treeSize; //testing reason
	const static int thisTree = -1;
	const static int childNW = 0;
	const static int childNE = 1;
	const static int childSW = 2;
	const static int childSE = 3;
	struct Node 
	{
		int maxLevel; //how many times node might be divided
		int maxElements;
		Node* parent;
		std::array<std::unique_ptr<Node>, 4> children;
		std::vector<std::shared_ptr<CollisionComponent>> elements;
		sf::FloatRect bounds;
		Node(int MaxLevel, int MaxElements, Node* Parent, sf::FloatRect Bounds) :
			maxLevel(MaxLevel), maxElements(MaxElements), parent(Parent), bounds(Bounds) {}
	};
	Node head;
	sf::FloatRect size;//map size
	Node& search(Node& parent, std::shared_ptr<CollisionComponent> toFind);// returns node where object should be add to
	void split(Node& toSplit);
	int getChildIndexForObject(std::shared_ptr<CollisionComponent> element, Node& parent);
	std::vector<std::shared_ptr<CollisionComponent>> possibleOverlaps//TODO do not copy this
	(std::shared_ptr<CollisionComponent> object, Node& parentNode); // return object which might collide
	std::vector<std::shared_ptr<CollisionComponent>> addAllChildren(Node* parent);
public:
	Quadtree(int MaxLevel, int MaxElements, sf::FloatRect size);
	void add(std::shared_ptr<CollisionComponent> toAdd);
	void remove(std::shared_ptr<CollisionComponent> toRemove);
	std::vector<std::shared_ptr<CollisionComponent>> possibleOverlaps(std::shared_ptr<CollisionComponent> object);
	void update();//TODO to keep moving object in tree
	int getSize() const { return treeSize; }
};

