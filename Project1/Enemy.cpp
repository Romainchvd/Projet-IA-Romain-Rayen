#include "Enemy.hpp"
#include <cmath>
using namespace sf;

void Enemy::update(float deltaTime) {
	//Cette fonction est vide pour la classe Enemy qui n'est jamais présente directement. Le but est d'éviter que GOAPAgent, qui prend un GOAPEnemy hérité d'Enemy, ait une fonction indéfinie.
}


void Enemy::patrol() {
	//Idem
}
void Enemy::toggleDraw()
{
	if (doDraw)
		doDraw = false;
	else
		doDraw = true;
	if (isAlive)
		isAlive = false;
	else
		isAlive = true;
}

Enemy::Enemy(float x, float y) : Entity(x, y, Color::Green) {
	position = Vector2f(x, y); shape.setPosition(position);
}