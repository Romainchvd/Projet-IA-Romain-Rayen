#pragma once

#include <unordered_map>
#include <string>

class Blackboard {
private:
    std::unordered_map<int, int> data;
public:
    void SetValue(const int& key, int value);
    int GetValue(const int& key);
};