#include <iostream>
#include "exercise.hpp"

int main()
{
    SingleValue single_value{ 1 };
    ManyValues other_values;
    other_values.add(2);
    other_values.add(3);
    int result = sum({ &single_value, &other_values });

    std::cout << "Result is: " << result << std::endl;
    return 0;
}