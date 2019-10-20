#include "View.h"

View::View(std::shared_ptr<Object> CentralObject, float width, float height) :
	view(CentralObject->getPosition().getPosition(), { width, height })
{
	centralObject = CentralObject;
}

void View::update()
{
	view.setCenter(centralObject->getPosition().getPosition() + sf::Vector2f(centralObject->getSize()));
}
