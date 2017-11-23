#pragma once

namespace sf
{
	class RenderWindow;
}
class Player;

class Game
{
public:
	Game();
	~Game();

	void Update();

private:
	sf::RenderWindow* m_window;
	Player* m_player;
};