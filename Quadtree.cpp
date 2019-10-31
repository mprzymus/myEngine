#include "Quadtree.h"

Quadtree::Quadtree() : Quadtree(5, 5, 0, { 0, 0, 1920, 1080 }, nullptr) {}

Quadtree::Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent) : maxObjects(maxObjects), maxLevels(maxLevels), level(level), bounds(bounds), parent(parent) {}

void Quadtree::Insert(std::shared_ptr<CollisionComponent> object)
{
	if (!bounds.intersects(object->getBounds()))
	{
		return;
	}

	if (children[0] != nullptr)
	{
		int indexToPlaceObject = GetChildIndexForObject(object->getBounds());

		if (indexToPlaceObject != thisTree)
		{
			children[indexToPlaceObject]->Insert(object);
			return;
		}
	}

	objects.emplace_back(object);

	if (objects.size() > maxObjects&& level < maxLevels && children[0] == nullptr)
	{
		Split();

		auto objIterator = objects.begin();
		while (objIterator != objects.end())
		{
			auto obj = *objIterator;
			int indexToPlaceObject = GetChildIndexForObject(obj->getBounds());

			if (indexToPlaceObject != thisTree)
			{
				children[indexToPlaceObject]->Insert(obj);
				objIterator = objects.erase(objIterator);

			}
			else
			{
				++objIterator;
			}
		}
	}
}

void Quadtree::Remove(std::shared_ptr<CollisionComponent> object)
{
	int index = GetChildIndexForObject(object->getBounds());

	if (index == thisTree || children[index] == nullptr)
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (objects.at(i)->getOwner()->getId() == object->getOwner()->getId())
			{
				objects.erase(objects.begin() + i);
				break;
			}
		}
	}
	else
	{
		return children[index]->Remove(object);
	}
}

void Quadtree::Clear()
{
	objects.clear();

	for (int i = 0; i < 4; i++)
	{
		if (children[i] != nullptr)
		{
			children[i]->Clear();
			children[i] = nullptr;
		}
	}
}

std::vector<std::shared_ptr<CollisionComponent>> Quadtree::Search(std::shared_ptr<CollisionComponent> object)
{
	const sf::FloatRect area = object->getBounds();
	std::vector<std::shared_ptr<CollisionComponent>> possibleOverlaps;
	Search(area, possibleOverlaps);
	return possibleOverlaps;
}

void Quadtree::Search(const sf::FloatRect& area,
	std::vector<std::shared_ptr<CollisionComponent>>& overlappingObjects)
{
	overlappingObjects.insert(overlappingObjects.end(), objects.begin(), objects.end());

	if (children[0] != nullptr)
	{
		int index = GetChildIndexForObject(area);

		if (index == thisTree)
		{
			for (int i = 0; i < 4; i++)
			{
				if (children[i]->GetBounds().intersects(area))
				{
					children[i]->Search(area, overlappingObjects);
				}
			}
		}
		else
		{
			children[index]->Search(area, overlappingObjects);
		}
	}
}

const sf::FloatRect& Quadtree::GetBounds() const
{
	return bounds;
}

int Quadtree::GetChildIndexForObject(const sf::FloatRect& objectBounds)
{
	int index = -1;
	float verticalDividingLine = bounds.left + bounds.width * 0.5f;
	float horizontalDividingLine = bounds.top + bounds.height * 0.5f;

	bool north = objectBounds.top < horizontalDividingLine && (objectBounds.height + objectBounds.top < horizontalDividingLine);
	bool south = objectBounds.top > horizontalDividingLine;
	bool west = objectBounds.left < verticalDividingLine && (objectBounds.left + objectBounds.width < verticalDividingLine);
	bool east = objectBounds.left > verticalDividingLine;

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

void Quadtree::Split()
{
	float childWidth = bounds.width / 2.f;
	float childHeight = bounds.height / 2.f;

	children[childNE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top, childWidth, childHeight), this);
	children[childNW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top, childWidth, childHeight), this);
	children[childSW] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left, bounds.top + childHeight, childWidth, childHeight), this);
	children[childSE] = std::make_shared<Quadtree>(maxObjects, maxLevels, level + 1, sf::FloatRect(bounds.left + childWidth, bounds.top + childHeight, childWidth, childHeight), this);
}
