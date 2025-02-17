#include "Enemy.hpp"
#include <cmath>
using namespace sf;
Enemy::Enemy(float x, float y) : Entity(x, y, sf::Color::Red) {}

void Enemy::update(float deltaTime, Grid& grid) {

}
void Enemy::chase(Player& player, Grid& grid)
{
	Vector2f movement(0.f, 0.f);
	if (player.shape.getPosition().x < shape.getPosition().x)
		movement.x -= 2;
	if (player.shape.getPosition().x > shape.getPosition().x)
		movement.x += 2;
	if (player.shape.getPosition().y < shape.getPosition().y)
		movement.y -= 2;
	if (player.shape.getPosition().y > shape.getPosition().y)
		movement.y += 2;
			Vector2f newPosition = shape.getPosition() + movement;
			FloatRect newBounds(newPosition, shape.getSize());
			auto isWalkable = [&](float x, float y) {
				int gridX = static_cast<int>(x / CELL_SIZE);
				int gridY = static_cast<int>(y / CELL_SIZE);
				return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
				};

			if (isWalkable(newBounds.left, newBounds.top) &&
				isWalkable(newBounds.left + newBounds.width - 1, newBounds.top) &&
				isWalkable(newBounds.left, newBounds.top + newBounds.height - 1) &&
				isWalkable(newBounds.left + newBounds.width - 1, newBounds.top + newBounds.height - 1)) {
				shape.move(movement);
			}
			
		
	
}