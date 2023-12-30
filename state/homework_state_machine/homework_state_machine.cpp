#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <utility>
#include <sstream>

using namespace std;

enum class States {
    LOCKED,
    OPEN,
    ERROR
};

enum class Transitions {
    CORRECTPASSWD,
    INCORRECTPASSWD,
    UNFINISHED
};

inline std::ostream& operator<<(std::ostream& os, States state) {
    switch (state) {
    case States::OPEN:
        os << "OPEN";
        break;
    case States::LOCKED:
        os << "LOCKED";
        break;
    case States::ERROR:
        os << "ERROR";
        break;
    default:
        std::cerr << "Invalid requested state" << std::endl;
    }
    return os;
}

inline std::ostream& operator<<(std::ostream& os, Transitions trans) {
    switch (trans) {
    case Transitions::CORRECTPASSWD:
        os << "Correct Password";
        break;
    case Transitions::INCORRECTPASSWD:
        os << "Incorrect Password";
        break;
    case Transitions::UNFINISHED:
        os << "Unfinished Password";
        break;
    default:
        std::cerr << "Invalid requested transition" << std::endl;
    }
    return os;
}

class CombinationLock
{
    vector<int> combination{}; // this is our password
    std::vector<int> insertedPw {};

    std::map<States, std::vector<std::pair<Transitions, States>>> transitionTable;

public:
    string status; // just for print out purposes
    States currentStatus{ States::LOCKED }; // initial state

    CombinationLock(const vector<int>& combination) : combination(combination) {
        // create transition table
        transitionTable.insert(
            { States::LOCKED,
                {
                    {Transitions::CORRECTPASSWD, States::OPEN},
                    {Transitions::INCORRECTPASSWD, States::ERROR},
                    {Transitions::UNFINISHED, States::LOCKED}
                }
            }
        );
        transitionTable.insert(
            { States::ERROR,
                {
                    {Transitions::CORRECTPASSWD, States::OPEN},
                    {Transitions::INCORRECTPASSWD, States::ERROR}
                }

            }
        );
        std::ostringstream oss;
        oss << currentStatus;
        status = oss.str();
    }

    void executeFSM() {
        // check condition
        Transitions tmpTransition;
        if (insertedPw.size() < combination.size()) {
            tmpTransition = Transitions::UNFINISHED;
        }
        else if (combination != insertedPw) {
            tmpTransition = Transitions::INCORRECTPASSWD;
        }
        else {
            tmpTransition = Transitions::CORRECTPASSWD;
        }

        // process transition table
        std::cout << "DEBUG: Transition is " << tmpTransition << std::endl;
        try {
            currentStatus = transitionTable.at(currentStatus).at(static_cast<int>(tmpTransition)).second;
        }
        catch (std::exception& e) {
            std::cout << "No transition found from " << currentStatus << " with transition " << tmpTransition << std::endl;
        }

        // convert internal status into the result string
        if (currentStatus == States::LOCKED) {
            std::string tmpResult{ "" };
            for (auto it : insertedPw) {
                tmpResult += std::to_string(it); // return the last inserted digit
            }
            status = tmpResult;
        }
        else {
            std::ostringstream tmpResultStr;
            tmpResultStr << currentStatus;
            status = tmpResultStr.str(); // return the lock or unlock status as the status text
        }
    }

    void enter_digit(int digit)
    {
        insertedPw.push_back(digit);
        executeFSM();
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