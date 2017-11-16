#include "KeyboardHandler.h"

bool* KeyboardHandler::keys = 0;

void KeyboardHandler::Initialize()
{
	keys = new bool[sf::Keyboard::KeyCount];
	for (size_t i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		keys[i] = false;
	}
}

void KeyboardHandler::setKeyDown(sf::Keyboard::Key key)
{
	keys[key] = true;
}

bool KeyboardHandler::isKeyDown(sf::Keyboard::Key key)
{
	return keys[key];
}

void KeyboardHandler::clearKeys()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		sf::Keyboard::Key key = sf::Keyboard::Key(i);
		if (sf::Keyboard::isKeyPressed(key))
			continue;

		keys[i] = false;
	}
}