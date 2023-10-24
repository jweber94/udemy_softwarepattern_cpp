#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

struct ContainsIntegers {
    virtual int absSum() = 0;
};

struct SingleValue : public ContainsIntegers
{
    int value{ 0 };

    SingleValue() = default;

    explicit SingleValue(const int value)
        : value{ value }
    {
    }

    int absSum() override {
        return value;
    }
};

struct ManyValues : vector<int>, public ContainsIntegers
{
    void add(const int value)
    {
        push_back(value);
    }

    int absSum() {
        return std::accumulate(this->begin(), this->end(), 0);
    }
};

int sum(const vector<ContainsIntegers*> items);