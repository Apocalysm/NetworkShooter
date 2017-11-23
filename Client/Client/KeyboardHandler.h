#pragma once
#include <SFML\Window\Keyboard.hpp>

class KeyboardHandler
{
public:
	static void Initialize();

	static void setKeyDown(sf::Keyboard::Key key);
	static bool isKeyDown(sf::Keyboard::Key key);
	static void clearKeys();

private:
	static bool* m_keys;
};