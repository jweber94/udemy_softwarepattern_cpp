#include <iostream>
#include <vector>

struct BankAccount {
	int balance{ 0 };
	int overdraft_limit{ -500 };

	void deposit(int amount) {
		balance += amount;
		std::cout << "deposit " << amount << ", balance is now " << balance << std::endl;
	}

	bool withdraw(int amount) { // by returing if the amount was successfully withdrawed, we can handle this information outside of the class and do not break the open-close principle
		if (balance - amount >= overdraft_limit) {
			balance -= amount;
			std::cout << "withdraw " << amount << ", balance is now " << balance << std::endl;
			return true;
		}
		std::cout << "Invalid withdraw - not enough money" << std::endl;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& ba) {
		os << "Balance is " << ba.balance;
		return os;
	}
};

struct Command {
	virtual void call() = 0;
	virtual void undo() = 0; // be careful with undo commands - they might lead to invalid actions, if the call() method was not executed before and/or was not executed properly
		// Also be careful - call and undo might not always be symetic in their application or depends on their history in combination with other Commands
	bool succeededCall{ false };
};

struct BankAccountCommand : public Command {
	// members
	BankAccount& account;
	int amount;
	enum Action { deposit, withdraw } action;

	// constructor
	BankAccountCommand(BankAccount& account, int amount, Action action) :
		account(account),
		amount(amount),
		action(action) 
	{}

	void call() override {
		switch (action) {
		case Action::deposit:
			account.deposit(amount);
			succeededCall = true;
			break;
		case Action::withdraw:
			succeededCall = account.withdraw(amount); // CAUTION: If the withdraw method is invalid because there was not enough money in the bank account by this invocation, then we cannot depsit the money of the command on the undo() method even if the call might be kind of symetic in its execution
			break;
		}
	}

	void undo() override { // we assume that our command is a symetic function to the call() method
		if (!succeededCall) { // the call operation already failed
			return;
		}
		switch (action) {
		case Action::withdraw:
			account.deposit(amount);
			break;
		case Action::deposit:
			account.withdraw(amount);
			break;
		}
	}
};

int main() {
	BankAccount ba;

	std::vector<BankAccountCommand> commands{
		BankAccountCommand{ba, 100, BankAccountCommand::Action::deposit},
		BankAccountCommand{ba, 50000, BankAccountCommand::Action::withdraw}
	};
	// bankaccount before we invoked the commands
	std::cout << ba << std::endl;
	std::cout << "Invoke the commands" << std::endl;
	for (auto& command : commands) { // we need the & because if we do not use it, we will create a deepcopy of the command and the succeededCall field will not get updated within the commands vector
		command.call();
	}
	std::cout << ba << std::endl;

	std::cout << "Undo the operations" << std::endl;
	for (auto it = commands.rbegin(); it != commands.rend(); ++it) {
		it->undo();
	}
	std::cout << ba << std::endl;
	return 0;
}