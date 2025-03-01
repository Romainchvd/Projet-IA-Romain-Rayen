// player.cpp
#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "Enemy.hpp"

using namespace std;
using namespace sf;
Player::Player(float x, float y, Grid& grid) : Entity(x, y, Color::Blue), grid(grid) {}

void Player::update(float deltaTime) {
    Vector2f movement(0.f, 0.f);
    if (Keyboard::isKeyPressed(Keyboard::Z)) movement.y -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::S)) movement.y += SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::Q)) movement.x -= SPEED * deltaTime;
    if (Keyboard::isKeyPressed(Keyboard::D)) movement.x += SPEED * deltaTime;

    Vector2f newPosition = shape.getPosition() + movement;
    FloatRect newBounds(newPosition, shape.getSize());

    // V�rifier les quatre coins du joueur
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
    hitbox.left =shape.getGlobalBounds().left - detectionMargin;
    hitbox.top = shape.getGlobalBounds().top - detectionMargin;
    hitbox.height = shape.getGlobalBounds().height + detectionMargin * 2;
    hitbox.width = shape.getGlobalBounds().width + detectionMargin * 2;

    endOfDetectionArea.left = shape.getGlobalBounds().left - endOfDetectionMargin;
    endOfDetectionArea.top = shape.getGlobalBounds().top - endOfDetectionMargin;
    endOfDetectionArea.height = shape.getGlobalBounds().height + endOfDetectionMargin * 2;
    endOfDetectionArea.width = shape.getGlobalBounds().width + endOfDetectionMargin * 2;
}

