#pragma once
#include <vector>
#include "Action.hpp"
enum class Goal {
    Patrouiller, Fuir
};


class GOAPPlanner {
public:
    std::vector<Action*> Plan(GOAPEnemy& enemy, Goal goal);
};