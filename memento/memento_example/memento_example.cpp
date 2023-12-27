#include <iostream>
#include <vector>
#include <memory>

// commonly a memento does not allow the user to see what state is stored in it. It also does NEVER allow to modify the state. Therefore, a memento typically has no accessor methods to the state information that it describes
class Memento {
	int balance;
public:
	Memento(int balance) : balance(balance) {}
	friend class BankAccount; // alternativly we can move the memento to the inner of the BankAccount class to have the BankAccount access to the private fields of the Memento class (since this is needed to restore the state from the memento due to the privately stored object state)
	friend class BankAccount2;
};


class BankAccount{
	int balance;

public:
	BankAccount(int balanceInit) : balance(balanceInit) {}

	Memento deposit(int amount) {
		balance += amount;
		return Memento{ balance };
	}

	// restore functionallity
	void restore(const Memento& m) {
		balance = m.balance;
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount& account) {
		os << "balance: " << account.balance;
		return os;
	}
};

class BankAccount2 {
	std::vector<std::shared_ptr<Memento>> history; // we want shared_ptr to the mementos, since we deliver them back to the deposit() method caller and we store them for the history at the same time
	unsigned int current{ 0 }; // pointer to the place where we are currently in our memento history - it describes the index of the history vector
	int balance{ 0 };

public:
	BankAccount2(int initBalance)
	{
		balance = initBalance;
		current = 0;
		history.push_back(std::shared_ptr<Memento>(new Memento(balance))); // emplace_back creates the pointer instance directly where we want it without the need of copying it 
	}

	std::shared_ptr<Memento> deposit(int amount) {
		balance += amount;
		history.push_back(std::shared_ptr<Memento>(new Memento(balance)));
		current = history.size() - 1; // -1 because the size starts at 1 but the index starts at 0
		return history.at(current);
	}

	void restore(const std::shared_ptr<Memento> snapshotToRestore) {
		if (snapshotToRestore != nullptr) {
			balance = snapshotToRestore->balance;
			history.push_back(snapshotToRestore);
			current = history.size() - 1;
		}
	}

	std::shared_ptr<Memento> undo() {
		// we need to be at least on the first step of our history
		if (current > 0) {
			current--; // we just roll back without adding to the history
			auto m = history.at(current);
			balance = m->balance;
			return m;
		}
		return { nullptr }; // invalid undo returns an empty shared_ptr<Memento>
	}

	std::shared_ptr<Memento> redo() {
		if (current + 1 < history.size()) { // check if we can redo something (we need to have something to be undone before - so our current index needs to be behind the actual size of the history)
			++current;
			auto m = history.at(current);
			balance = m->balance;
			return m;
		}
		return { nullptr };
	}

	friend std::ostream& operator<<(std::ostream& os, const BankAccount2 ba) {
		os << "balance = " << ba.balance;
		return os;
	}
};

int main() {
	std::cout << "*********** BankAccount1 **************" << std::endl;
	BankAccount ba(100);

	auto m1 = ba.deposit(50);
	auto m2 = ba.deposit(25);

	std::cout << ba << std::endl;

	ba.restore(m1);
	std::cout << ba << std::endl;

	std::cout << "*********** BankAccount2 **************" << std::endl;
	BankAccount2 ba2{ 100 };
	ba2.deposit(50);
	ba2.deposit(25);
	std::cout << ba2 << std::endl;
	ba2.undo();
	std::cout << "Undo 1" << std::endl;
	std::cout << ba2 << std::endl;
	ba2.undo();
	std::cout << "Undo 2" << std::endl;
	std::cout << ba2 << std::endl;
	ba2.redo();
	std::cout << "Redo 1" << std::endl;
	std::cout << ba2 << std::endl;

	return 0;
}