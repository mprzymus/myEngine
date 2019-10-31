#pragma once
#include <memory>

class Object;
class Component
{
protected:
	Object* owner;
public:
	Component(std::shared_ptr<Object> owner) : owner(owner.get()) {}
	Component(Object* owner) : owner(owner) {}
	virtual ~Component() {}
	virtual void update(float timeElapsed) = 0;
};

