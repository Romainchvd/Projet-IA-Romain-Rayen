#pragma once
#include "Enemy.hpp"
enum State { PATROL, CHASE, SEARCH };

class FSMEnemy : public Enemy
{
public:
	FSMEnemy(float x , float y, Grid& grid, Player& player);
	void patroll() override;
	void update(float deltaTime, Grid& grid) override;
	void runFSM(float deltaTime);
	void chase();
	void checkDetection();
	void search(float deltaTime);
	Vector2f lastPlayerPosition;
	Grid& grid;
	Player& player;
	int PlayerDetected = 0;
	State currentState = PATROL;
	bool isSearching = false;
};

