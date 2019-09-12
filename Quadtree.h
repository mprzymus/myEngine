#pragma once
#include <array>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "CollisionComponent.h"

class Quadtree
{
	const static int thisTree = -1;
	const static int childNW = 0;
	const static int childNE = 1;
	const static int childSW = 2;
	const static int childSE = 3;
	struct Node 
	{
		int maxLevel;
		int maxElements;
		Node* parent;
		std::array<std::unique_ptr<Node>, 4> children;
		std::vector<std::shared_ptr<CollisionComponent>> elements;
		sf::FloatRect bounds;
		Node(int MaxLevel, int MaxElements, Node* Parent, sf::FloatRect Bounds) :
			maxLevel(MaxLevel), maxElements(MaxElements), parent(Parent), bounds(Bounds) {}
	};
	Node head;
	sf::FloatRect size;
	Node& search(Node& parent, std::shared_ptr<CollisionComponent> toFind);
	void split(Node& toSplit);
	int getChildIndexForObject(std::shared_ptr<CollisionComponent> element, Node& parent);
public:
	Quadtree(int MaxLevel, int MaxElements, sf::FloatRect size);
	void add(std::shared_ptr<CollisionComponent> toAdd);
	void remove(std::shared_ptr<CollisionComponent> toRemove);
	void update();
};

