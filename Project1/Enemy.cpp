#include "Enemy.hpp"
#include <cmath>
using namespace sf;

void Enemy::update(float deltaTime, Grid& grid) {

}


void Enemy::patrol() {

		
}

Enemy::Enemy(float x, float y) : Entity(x, y, Color::Green) {
	position = Vector2f(x, y); shape.setPosition(position);
}