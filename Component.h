#pragma once
#include <memory>
class Object;
class Component
{
protected:
	Object* owner;
public:
	virtual void update(float timeElapsed) = 0;
};

