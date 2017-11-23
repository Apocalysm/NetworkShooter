#include "KeyboardHandler.h"

bool* KeyboardHandler::m_keys = 0;

void KeyboardHandler::Initialize()
{
	m_keys = new bool[sf::Keyboard::KeyCount];
	for (size_t i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		m_keys[i] = false;
	}
}

void KeyboardHandler::setKeyDown(sf::Keyboard::Key key)
{
	m_keys[key] = true;
}

bool KeyboardHandler::isKeyDown(sf::Keyboard::Key key)
{
	return m_keys[key];
}

void KeyboardHandler::clearKeys()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; i++)
	{
		sf::Keyboard::Key key = sf::Keyboard::Key(i);
		if (sf::Keyboard::isKeyPressed(key))
			continue;

		m_keys[i] = false;
	}
}