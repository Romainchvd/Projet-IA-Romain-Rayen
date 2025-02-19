#include "GOAPPlanner.hpp"

std::vector<Action*> GOAPPlanner::Plan(GOAPEnemy& enemy, Goal goal) {
    std::vector<Action*> plan;

    if (goal == Goal::Fuir) {
        plan.push_back(new RunAway);
    }
    else if (goal == Goal::Patrouiller) {
        plan.push_back(new Patrol);
    }

    return plan;
}