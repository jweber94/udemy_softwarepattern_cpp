#include <iostream>
struct Command
{
    enum Action { deposit, withdraw } action;
    int amount{ 0 };
    bool success{ false };
};

struct Account
{
    int balance{ 0 };

    void process(Command& cmd)
    {
        cmd.success = true;
        if (cmd.action == Command::Action::deposit)
        {
            balance += cmd.amount;
        }
        else if (cmd.action == Command::Action::withdraw)
        {
            if (balance - cmd.amount <= 0) {
                cmd.success = false;
            }
            else {
                balance -= cmd.amount;
            }
        }
        else
        {
            cmd.success = false;
            std::cerr << "Invalid requested action";
        }
    }
};