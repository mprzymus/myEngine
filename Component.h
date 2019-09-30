#pragma once
#include <memory>

class Object;
class Component
{
protected:
	std::weak_ptr<Object> owner;
public:
	virtual ~Component() {}
	virtual void update(float timeElapsed) = 0;
};

