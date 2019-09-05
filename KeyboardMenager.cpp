#include "KeyboardMenager.h"
#include <SFML/Window/Event.hpp>
#include <iostream>
KeyboardMenager::KeyboardMenager()
{
	//TODO save users keyboard prefferences
	//so far I hardcode it

	keys.push_back(std::pair<input, sf::Keyboard::Key>(Left, sf::Keyboard::Key::Left));
	keys.push_back(std::pair<input, sf::Keyboard::Key>(Right, sf::Keyboard::Key::Right));
	keys.push_back(std::pair<input, sf::Keyboard::Key>(Jump, sf::Keyboard::Key::Space));
}

const std::vector<KeyboardMenager::input>& KeyboardMenager::currentInput()
{
	toReturn.clear();
	for (auto& key : keys)
	{
		if (sf::Keyboard::isKeyPressed(key.second))
		{
			//std::cout << key.second << std::endl;
			toReturn.push_back(key.first);
		}
	}
	return toReturn;
}
