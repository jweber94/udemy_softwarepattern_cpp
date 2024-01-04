#include <iostream>
#include <typeindex>
#include <map>

struct GameObject;

void collide(GameObject& first, GameObject& second);

// Define an interface and a call to the global collide method which uses the current game object, combined with a handed over argument
struct GameObject {
	virtual std::type_index type() const = 0;

	virtual void collide(GameObject& other) {
		::collide(*this, other);
	}
};

// CRTP to deduce a type
template <typename T>
struct GameObjectImpl : public GameObject {
	std::type_index type() const override {
		return typeid(T);
	}
};

// derived classes as differenciations of the game object implementation
struct Planet : public GameObjectImpl<Planet> {

};

struct Asteroid : public GameObjectImpl<Asteroid> {

};

struct Spaceship : public GameObjectImpl<Spaceship> {

};

// methods that should be dispatched at runtime
void spaceship_planet() {
	std::cout << "Spaceship lands on a planet\n";
}
void asteroid_planet() {
	std::cout << "Asteroid burns in the athmosphere\n";
}
void asteroid_spaceship() {
	std::cout << "Asteroid hits and destroys spaceship\n";
}

// LUT for the multi-dispatching based on the typeid
std::map<std::pair<std::type_index, std::type_index>, void(*)(void)> outcomes{
	{{typeid(Spaceship), typeid(Planet)}, spaceship_planet},
	{{typeid(Asteroid), typeid(Planet)}, asteroid_planet},
	{{typeid(Asteroid), typeid(Spaceship)}, asteroid_spaceship}
};

// dispatching function
void collide(GameObject& first, GameObject& second) {
	auto it = outcomes.find({ first.type(), second.type() }); // direct collision check
	if (it == outcomes.end()) {
		it = outcomes.find({ second.type(), first.type() });
		if (it == outcomes.end()) { // reverse collision check
			std::cout << "Object pass each other harmlessly\n";
			return;
		}
	}
	it->second(); // invoke the function pointer - generating the appropriated result
}

int main() {
	Asteroid asteroid;
	Spaceship spaceship;
	Planet planet;

	collide(planet, spaceship);
	collide(planet, asteroid);
	collide(spaceship, asteroid);
	collide(planet, planet);
	return 0;
}