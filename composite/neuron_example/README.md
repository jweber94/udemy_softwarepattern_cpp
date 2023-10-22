# Neuron example with CRTP

## Curriously Recurring Template Pattern (CRTP)
+ The aim of the Curriously Recurring Template Pattern is to deliver base class methods to derived classes without the need of virtual methods and therefor avoiding complicated and runtíme and memory intense inheritance structures at runtime
	- Because the inheritance is based on the template argument which is the derived class itself, the compiler implements the methods for the derived class. In that way, no VTable is realized for our implementation which leads to a more runtime efficient and also memory efficient executable code				* It does not complicate the inheritance structure on execution time
		* We implement _static polymorphy_ with it: The compiler checks if the template implementation can properly deduced from our defined inheritance structure from the precompiler
+ Basically we take the advantages of the runtime and memory efficency with the CRTP, but we can also enforce the implementation of methods in the derived classes by casting and calling them within the templated base class in the CRTP
	- This is what we do in our neuron_example.cpp
+ Since the templated base class acts like an abstract base class (which is based on (pure-)virtual methods) but does not use VTables under the hood, the CRTP is much more efficient with regard to execution performance and (RAM) memory demand like it was said before and therefor a good choice for abstractions in embedded systems software

### Example for avoiding the reimplementation of code in all derived classes
```
#include <iostream>
template <typename Derived>
class Base {
public:
    void commonFunc() {
        // Gemeinsame Implementierung in der Basisklasse.
        std::cout << "Common functionality in Base" << std::endl;
    }
};

class DerivedA : public Base<DerivedA> {
public:
    // Die spezialisierte Methode für DerivedA.
    void specificFunc() {
        std::cout << "Specific functionality in DerivedA" << std::endl;
    }
};

class DerivedB : public Base<DerivedB> {
public:
    // Die spezialisierte Methode für DerivedB.
    void specificFunc() {
        std::cout << "Specific functionality in DerivedB" << std::endl;
    }
};

int main() {
    DerivedA objA;
    objA.commonFunc();  // Ruft commonFunc aus Base auf ohne VTable und ohne mehrfach implementierung
    objA.specificFunc(); // Ruft specificFunc in DerivedA auf

    DerivedB objB;
    objB.commonFunc();  // Ruft commonFunc aus Base auf ohne VTable und ohne mehrfach implementierung
    objB.specificFunc(); // Ruft specificFunc in DerivedB auf

    return 0;
}
```
which delivers:
```
Common functionality in Base
Specific functionality in DerivedA
Common functionality in Base
Specific functionality in DerivedB
```

### Example for enforcing method implementations in derived classes without creating VTables (aka static polymorphism)
```
#include <iostream>
template <typename Derived>
class Base {
public:
    void commonFunc() {
        // Gemeinsame Implementierung in der Basisklasse.
        std::cout << "Common functionality in Base" << std::endl;
        // Aufruf der spezialisierten Methode, die in Derived implementiert werden muss.
        static_cast<Derived*>(this)->specificFunc(); // enforces the implementation of specificFunc in all derived classes that inherits from this base class at compile time - static polymorphism
    }
};

class DerivedA : public Base<DerivedA> {
public:
    // Implementiert die spezialisierte Methode für DerivedA.
    void specificFunc() {
        std::cout << "Specific functionality in DerivedA" << std::endl;
    }
};

class DerivedB : public Base<DerivedB> {
public:
    // Implementiert die spezialisierte Methode für DerivedB.
    void specificFunc() {
        std::cout << "Specific functionality in DerivedB" << std::endl;
    }
};

int main() {
    DerivedA objA;
    objA.commonFunc();  // Ruft commonFunc aus Base auf

    DerivedB objB;
    objB.commonFunc();  // Ruft commonFunc aus Base auf

    return 0;
}

```
which delivers:
```
Common functionality in Base
Specific functionality in DerivedA
Common functionality in Base
Specific functionality in DerivedB
```

## Neuron example: Main takeaways
+ By finding a way (in this case the range based for loop) that can be implemented for the single class as well as for the compond class within the CRTP method, we can use the composite method from the templated CRTP base class in both scenarios: in the single class as well as the compond class
    - To be able to do this, we needed to make the single neuron to a range based element by implementing the `Self* begin()` and `Self* end()` methods of it
    - If the `NeuronLayer` havn't had inherited from the `std::vector<Neuron>`, we need to implement the `begin()` and `end()` method here as well

## Mixin Pattern
+ Is not the same as the composite pattern, but also can make use of the CRTP!
+ We define some Mixin templated base classes and these can (but must not) be inherited by the derived class and thereby the functionallity of the dervived classes get enhanced
    - In that way we are able to add or remove functionallity just by inheriting
+ Main advantages:
    - Reuse of code: We can reuse implemented functionallities without reimplementation of the same functionallity in multiple classes
    - Decoupleing: We can add or remove the mixin functionallity without changing the mixin class itself - only the derived (user of the mixin class) needs to be adjusted
    - Flexibility: We can enforce dervied class specific implementations by using the CRTP or pure virtual methods in the mixin class

### Example of the Mixin Pattern but without CRTP
```
#include <iostream>
#include <string>

// Ein Mixin für die Debug-Ausgabe
class DebugMixin {
public:
    void debug(const std::string& message) {
        std::cout << "Debug: " << message << std::endl;
    }
};

// Ein weiteres Mixin für die Protokollierung
class LogMixin {
public:
    void log(const std::string& message) {
        std::cout << "Log: " << message << std::endl;
    }
};

// Eine Klasse, die beide Mixins verwendet
class MyClass : public DebugMixin, public LogMixin {
public:
    void doSomething() {
        debug("Starting doSomething...");
        log("Doing some work...");
        // Führen Sie hier die eigentliche Arbeit aus.
        debug("doSomething finished.");
    }
};

int main() {
    MyClass obj;
    obj.doSomething();

    return 0;
}
```

### Example of the Mixin Pattern with the CRTP
```
#include <iostream>

// Mixin: Drawable
template<typename Derived>
class Drawable {
public:
    void draw() {
        std::cout << "Drawing a " << static_cast<Derived*>(this)->getName() << std::endl;
    }
};

// Mixin: Movable
template<typename Derived>
class Movable {
public:
    void move(int x, int y) {
        std::cout << "Moving " << static_cast<Derived*>(this)->getName() << " to (" << x << ", " << y << ")" << std::endl;
    }
};

// Concrete class using mixins
class Sprite : public Drawable<Sprite>, public Movable<Sprite> {
public:
    Sprite(const std::string& name) : name(name) {}

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

int main() {
    Sprite sprite("Hero");

    sprite.draw();
    sprite.move(10, 20);

    return 0;
}
```