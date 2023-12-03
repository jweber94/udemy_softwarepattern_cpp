#include <iostream>

// We could enhance this property template class with functionallity that should be applied to the properties that act (API wise) as a normal field.
template <typename T>
struct Property {
	T value; // underlying object

	Property(T value) {
		*this = value; // calls the overloaded operator= (line 12 ff)
	}

	/* Accessors - these are the actual proxy implementation */
	// setter
	T operator=(T newVal) {
		std::cout << "Assignment\n";
		value = newVal;
		return value;
	}

	// getter
	operator T() {
		return value;
	}
};

// If we need additional behaviour for specific template arguments (e.g. self written classes), we can do this by template specification
// Or we work via inheritance and method overloading with the property proxy (see additional example)

struct BadCreatur {
	// fields
	int strength = 10;
	int agility = 10;

	// getters and setters
	int getStrength() {
		return strength;
	}
	void setStrength(int newStr) {
		strength = newStr;
	}

	int getAgility() {
		return agility;
	}
	void setAgility(int newAgil) {
		agility = newAgil;
	}
};


struct Creatur {
	// usage of the proxy
	Property<int> strength{ 10 };	// by using the property proxy, the propery acts like a basic member. Therefore we do not need to implement getters and setters. We can access it like normal fields
	Property<int> agility{ 12 };	// The property might have additional functionallity to the field but the accessor API (via normal access of fields in a class) stays the same
};

int main() {

	BadCreatur bc;
	bc.setStrength(42);
	std::cout << "Bad creatur agility is " << bc.getAgility() << std::endl;

	// usage of the proxy - common accessor API is recreated by it
	Creatur c;
	c.strength = 15;
	std::cout << "Creatur agility is " << c.agility << std::endl;

	return 0;
}