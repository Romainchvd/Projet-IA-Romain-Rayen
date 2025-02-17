#ifndef PNJ_H
#define PNJ_H

#include <SFML/Graphics.hpp>
#include <cmath>
using namespace std;
using namespace sf;

class PNJ {
public:
    Vector2f position;
    float detectionRadius;
    CircleShape circle;
    Vector2f lastPlayerPosition;
    enum State { PATROL, CHASE, SEARCH };
    State currentState;



    PNJ(Vector2f startPos, float radius, float radiusCircle);

    bool detectPlayer(Vector2f playerPos);
    void patrol();
    void chase(Vector2f playerPos);
    void update(Vector2f playerPos, float deltaTime);
    void search(Vector2f lastPlayerPos, float deltaTime);
};

#endif