#include "Quadtree.h"

Quadtree::Node& Quadtree::search(Node& parent, std::shared_ptr<CollisionComponent> toFind)
{
	int index = getChildIndexForObject(toFind, parent);
	Node* node = &parent;
	while (index != thisTree)
	{
		node = parent.children.at(index).get();
		index = getChildIndexForObject(toFind, *node);
	}
	return *node;
}

void Quadtree::split(Node& toSplit)
{
	if (toSplit.children.at(0) != nullptr) return;
	const float childWidth = toSplit.bounds.width / 2;
	const float childHeight = toSplit.bounds.height / 2;
	toSplit.children[0] = std::make_unique<Node>(toSplit.maxLevel-1, toSplit.maxElements, &toSplit,
		sf::FloatRect(toSplit.bounds.left, toSplit.bounds.top, childWidth, childHeight));
	toSplit.children[1] = std::make_unique<Node>(toSplit.maxLevel - 1, toSplit.maxElements, &toSplit,
		sf::FloatRect(toSplit.bounds.left + childWidth, toSplit.bounds.top, childWidth, childHeight));
	toSplit.children[2] = std::make_unique<Node>(toSplit.maxLevel - 1, toSplit.maxElements, &toSplit,
		sf::FloatRect(toSplit.bounds.left, toSplit.bounds.top + childHeight, childWidth, childHeight));
	toSplit.children[3] = std::make_unique<Node>(toSplit.maxLevel - 1, toSplit.maxElements, &toSplit,
		sf::FloatRect(toSplit.bounds.left + childWidth, toSplit.bounds.top + childHeight, childWidth, childHeight));
}

int Quadtree::getChildIndexForObject(std::shared_ptr<CollisionComponent> element, Node& parent)
{
	int index = -1;
	float verticalDividingLine = parent.bounds.left + parent.bounds.width * 0.5f;
	float horizontalDividingLine = parent.bounds.top + parent.bounds.height * 0.5f;

	bool north = element->getTop() < horizontalDividingLine
		&& (element->getHeight() + element->getTop() < horizontalDividingLine);
	bool south = element->getTop() > horizontalDividingLine;
	bool west = element->getLeft()< verticalDividingLine
		&& (element->getLeft() + element->getWidth() < verticalDividingLine);
	bool east = element->getLeft() > verticalDividingLine;
	if (east)
	{
		if (north)
		{
			index = childNE;
		}
		else if (south)
		{
			index = childSE;
		}
	}
	else if (west)
	{
		if (north)
		{
			index = childNW;
		}
		else if (south)
		{
			index = childSW;
		}
	}
	return index;
}

Quadtree::Quadtree(int MaxLevel, int MaxElements, sf::FloatRect size) :
	head(MaxLevel, MaxElements, nullptr, size)
{
	head.maxElements = MaxElements;
	head.maxLevel = MaxLevel;
	head.parent = nullptr;
	head.bounds = this->size = size;
}

void Quadtree::add(std::shared_ptr<CollisionComponent> toAdd)
{
	Node* area = &search(head, toAdd);
	if (area->elements.size() >= area->maxElements)
	{
		split(*area);
		area = &search(*area, toAdd);
	}
	area->elements.push_back(toAdd);
}

void Quadtree::remove(std::shared_ptr<CollisionComponent> toRemove)
{
	Node& node = search(head, toRemove);
	node.elements.erase(std::find(node.elements.begin(), node.elements.end(), toRemove));
}

