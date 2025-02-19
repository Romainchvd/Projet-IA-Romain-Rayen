#pragma once
#include "GOAPEnemy.hpp"
class Action {
public:
    virtual bool CanExecute(const GOAPEnemy& enemy) = 0;
    virtual void Execute(GOAPEnemy& enemy) = 0;
    virtual ~Action() {}
};

class Patrol : public Action {
public:
    bool CanExecute(const GOAPEnemy& enemy) override;

    void Execute(GOAPEnemy& enemy) override;
};

class RunAway : public Action {
public:
    bool CanExecute(const GOAPEnemy& enemy) override;

    void Execute(GOAPEnemy& enemy) override;
};