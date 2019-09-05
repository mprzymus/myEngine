#pragma once
#include <vector>
#include <utility>
#include <SFML/Window/Keyboard.hpp>

class KeyboardMenager
{
public:
	enum input
	{
		None,
		Right,
		Left,
		Jump
	};
private:
	std::vector<std::pair<input, sf::Keyboard::Key>> keys;
	std::vector<input> toReturn;
public:
	KeyboardMenager();
	const std::vector<input>& currentInput();
};

