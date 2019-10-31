#pragma once
#include "Component.h"
class IdComponent :
	public Component
{
	static int count;
	int id;

public:
	IdComponent(Object* owner);
	IdComponent(std::shared_ptr<Object> owner);
	int getId() const;
	void update(float) override {}
};

