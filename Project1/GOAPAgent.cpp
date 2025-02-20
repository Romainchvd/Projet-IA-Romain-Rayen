#include "GOAPAgent.hpp"

void GOAPAgent::PerformActions() {
    Goal goal;
    enemy.checkPlayerDetected();
    enemy.checkColision();
    if (enemy.PlayerDetected)
        goal = Goal::Fuir;
    else
        goal = Goal::Patrouiller;
    
    std::vector<Action*> plan = planner.Plan(enemy, goal);
    
    for (auto action : plan) {
        if (action->CanExecute(enemy)) {
            action->Execute(enemy);
        }
        else {
            std::cout << "Action impossible : " << typeid(*action).name() << "\n";
        }
        delete action;
    }
}
GOAPAgent::GOAPAgent(float x, float y, Player& player, Grid& grid) : enemy(x, y, player, grid) { enemy.shape.setPosition(x, y); }