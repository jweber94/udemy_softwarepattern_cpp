#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CombinationLock
{
    vector<int> combination;
public:
    string status;

    CombinationLock(const vector<int>& combination) : combination(combination) {

    }

    void enter_digit(int digit)
    {
        // TODO
    }
};

int main() {
    CombinationLock cl({ 1,2,3 });
    std::cout << "Expected status is LOCKED, actual status is " << cl.status << std::endl;
    cl.enter_digit(1);
    std::cout << "Expected status is 1, actual status is " << cl.status << std::endl;
    cl.enter_digit(2);
    std::cout << "Expected status is 12, actual status is " << cl.status << std::endl;
    cl.enter_digit(3);
    std::cout << "Expected status is OPEN, actual status is " << cl.status << std::endl;

	return 0;
}