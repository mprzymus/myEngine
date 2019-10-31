#include "IdComponent.h"

int IdComponent::count = 0;

IdComponent::IdComponent(Object* owner) : Component(owner), id(count++)
{}

IdComponent::IdComponent(std::shared_ptr<Object> owner) : Component(owner), id(count++)
{}

int IdComponent::getId() const
{
	return id;
}
