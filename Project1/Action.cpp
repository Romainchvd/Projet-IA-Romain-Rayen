#include "Action.hpp"

bool Patrol::CanExecute(const GOAPEnemy& enemy)
{
        return !enemy.PlayerDetected;
}
void Patrol::Execute(GOAPEnemy& enemy) {
        std::cout << "L'agent patrouille.\n";
        enemy.patrol();
    }

bool RunAway::CanExecute(const GOAPEnemy& enemy) {
    return enemy.PlayerDetected;
}

void RunAway::Execute(GOAPEnemy& enemy) {
    std::cout << "L'agent fuit.\n";
    enemy.runAway();
}