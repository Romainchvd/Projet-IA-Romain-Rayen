#pragma once
#include "Player.hpp"
#include <vector>
#include "BTEnemy.hpp"
#include "FSMEnemy.hpp"
#include "GOAPAgent.hpp"
using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

class Game
{
public:
	RenderWindow& window;
	Grid grid;
	Player player;
	Clock clock;
	BTEnemy btEnemy;
	GOAPAgent goapEnemy;
	FSMEnemy fsmEnemy;
	void run();
	void update();
	void draw();
	void input();
	bool isRunning = true;
	Game(RenderWindow& window);
};

