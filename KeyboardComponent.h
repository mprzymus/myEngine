#pragma once
#include "Component.h"
#include "KeyboardMenager.h"
class KeyboardComponent :
	public Component
{
	KeyboardMenager& menager;
public:
	KeyboardComponent(KeyboardMenager& menager, std::shared_ptr<Object> owner) 
		: menager(menager) {
		this->owner = owner;
	}
	virtual void update(float timeElapsed) override;
};

