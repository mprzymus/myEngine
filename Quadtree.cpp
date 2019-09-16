#include "Quadtree.h"

Quadtree::Node& Quadtree::search(Node& parent, std::shared_ptr<CollisionComponent> toFind)
{
	int index = getChildIndexForObject(toFind, parent);
	Node* node = &parent;
	while (index != thisTree && node->children.at(index).get() != nullptr)
	{
		node = node->children.at(index).get();
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
	if (area->elements.size() <= area->maxElements)
	{
		split(*area);
		auto it = area->elements.begin();
		while (it != area->elements.end())
		{
			int index = getChildIndexForObject(*it, *area);
			if (index != thisTree)
			{
				area->children.at(index)->elements.push_back(*it);
				it = area->elements.erase(it);
			}
			else
				it++;
		}
		area = &search(*area, toAdd);
	}
	area->elements.push_back(toAdd);
}

void Quadtree::remove(std::shared_ptr<CollisionComponent> toRemove)
{
	Node& node = search(head, toRemove);
	node.elements.erase(std::find(node.elements.begin(), node.elements.end(), toRemove));
}

std::vector<std::shared_ptr<CollisionComponent>> Quadtree::possibleOverlaps(std::shared_ptr<CollisionComponent> object)
{
	return possibleOverlaps(object, head);
}
std::vector<std::shared_ptr<CollisionComponent>> Quadtree::possibleOverlaps(std::shared_ptr<CollisionComponent> object, Node& parentNode)
{
	std::vector<std::shared_ptr<CollisionComponent>> toReturn;
	Node* node = &search(parentNode, object);
	toReturn.insert(toReturn.end(), node->elements.begin(), node->elements.end());
	if (node->children.at(0).get() != nullptr)
	{
		for (auto& element : node->children)
		{
			auto temp = possibleOverlaps(object, *element);
			toReturn.insert(toReturn.end(), temp.begin(), temp.end());
		}
	}
	return toReturn;
}

