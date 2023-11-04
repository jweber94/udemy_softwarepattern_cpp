#include <iostream>

// Definition des Concepts
template <typename T>
concept HasMethodMandatory = requires(T obj, int i) {
    { obj.methodMandatory(i) } -> std::same_as<void>; // Überprüfen Sie, ob die Methode existiert und void zurückgibt
};

// Eine Klasse, die die erforderliche Methode enthält
class MyClass {
public:
    void methodMandatory(int i) {
        std::cout << "MethodMandatory called with " << i << std::endl;
    }
};

// Eine Klasse, die die erforderliche Methode nicht enthält
class AnotherClass {
public:
    void anotherMethod(int i) {
        std::cout << "AnotherMethod called with " << i << std::endl;
    }
};

// Eine templateisierte Klasse, die das Concept verwendet
template <HasMethodMandatory T>
class TemplateClass {
public:
    void useMethod(T obj, int i) {
        obj.methodMandatory(i); // Verwenden Sie die Methode, da das Concept erfüllt ist
    }
};

int main() {
    MyClass myObj;
    AnotherClass anotherObj;

    // Verwenden Sie die templateisierte Klasse mit dem Concept
    TemplateClass<MyClass> templateObj;
    templateObj.useMethod(myObj, 42); // Ruft die Methode in MyClass auf

    // Die folgende Zeile würde einen Kompilierungsfehler verursachen, da AnotherClass das Concept nicht erfüllt:
    // TemplateClass<AnotherClass> templateObj2; // Fehler: Concept HasMethodMandatory<AnotherClass> is not satisfied

    return 0;
}