#include "Blackboard.hpp"


void Blackboard::SetValue(const int& key, int value) {
    data[key] = value;
}
int Blackboard::GetValue(const int& key) {
    return data[key];
}