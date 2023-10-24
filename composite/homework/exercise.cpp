#include "exercise.hpp"

int sum(const vector<ContainsIntegers*> items)
{
    int result{ 0 };
    for (auto it : items) {
        result += it->absSum();
    }
    return result;
}