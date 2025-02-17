#pragma once

#include <unordered_map>
#include <string>
using namespace std;
class Blackboard {
private:
    unordered_map<int, int> data;
public:
    void SetValue(const int& key, int value);
    int GetValue(const int& key);
};