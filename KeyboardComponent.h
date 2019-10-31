#pragma once
#include <exception>
#include "Object.h"
#include "Component.h"
#include "KeyboardMenager.h"
#include "DynamicPositionComponent.h"
#include "Gravity.h"

class KeyboardComponent :
	public Component
{
	KeyboardMenager& menager;
	DynamicPositionComponent* position;
	Gravity& gravity;

public:
	KeyboardComponent(KeyboardMenager& menager, std::shared_ptr<Object> owner, Gravity& gravity) 
		: Component(owner), menager(menager), gravity(gravity) {
		position = dynamic_cast<DynamicPositionComponent*>(&owner->getPosition());
		if (position == nullptr)
			throw std::invalid_argument("Only object with DynamicPositionComponent can be moved by keyboard");
	}
	virtual void update(float timeElapsed) override;
};

