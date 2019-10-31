#include <memory>
#include <vector>

#include "CollisionComponent.h"
#include "Object.h"

class Quadtree
{
public:
	Quadtree();
	Quadtree(int maxObjects, int maxLevels, int level, sf::FloatRect bounds, Quadtree* parent);

	void Insert(std::shared_ptr<CollisionComponent> object);
	void Remove(std::shared_ptr<CollisionComponent> object);
	void Clear();

	std::vector<std::shared_ptr<CollisionComponent>> Search(std::shared_ptr<CollisionComponent> object);

	const sf::FloatRect& GetBounds() const;

private:
	void Search(const sf::FloatRect& area, std::vector<std::shared_ptr<CollisionComponent>>& overlappingObjects);

	int GetChildIndexForObject(const sf::FloatRect& objectBounds);
	void Split();

	static const int thisTree = -1;
	static const int childNE = 0;
	static const int childNW = 1;
	static const int childSW = 2;
	static const int childSE = 3;

	int maxObjects;
	int maxLevels;

	Quadtree* parent;
	std::shared_ptr<Quadtree> children[4];

	std::vector<std::shared_ptr<CollisionComponent>> objects;

	int level;

	sf::FloatRect bounds;
};