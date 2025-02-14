#ifndef PNJ_H
#define PNJ_H

#include <SFML/Graphics.hpp>
#include <cmath>

class PNJ {
public:
    sf::Vector2f position;
    float detectionRadius;
    sf::CircleShape circle;
    sf::Vector2f lastPlayerPosition;
    enum State { PATROL, CHASE, SEARCH };
    State currentState;



    PNJ(sf::Vector2f startPos, float radius, float radiusCircle);

    bool detectPlayer(sf::Vector2f playerPos);
    void patrol();
    void chase(sf::Vector2f playerPos);
    void update(sf::Vector2f playerPos, float deltaTime);
    void search(sf::Vector2f lastPlayerPos, float deltaTime);
};

#endif