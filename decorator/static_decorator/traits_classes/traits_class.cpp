#include <iostream>

// default implementation of the traits class
template <typename T>
struct is_arithmetic_trait {
    static const bool value = false; // on default, the is_arithmetic_trait::value is always false
};

// specialization of the traits class for int
template <> // the empty template argument indicates that you want to define a template specification
struct is_arithmetic_trait<int> {
    static const bool value = true;
};

// specialization of the traits class for float
template <>
struct is_arithmetic_trait<float> {
    static const bool value = true;
};

// example basic usage of the traits class
template <typename T> // common use case of traits classes - we can control the behaviour of the method at compile time (and the compiler can optimize the else branch away)
void someFunction() {
    if (is_arithmetic_trait<T>::value) {
        std::cout << "Type T is arithmetic." << std::endl;
    } else {
        std::cout << "Type T is not arithmetic." << std::endl;
    }
}


/* Traits classes with methods */
class MyClass {
    // TODO
};

template <typename T>
struct MyTraits {
    static bool hasSpecialFeature() {
        // Fancy common behaviour of the class
        return false;
    }
};

// 
template <>
struct MyTraits<MyClass> {
    static bool hasSpecialFeature() {
        // specific behaviour for the MyClass
        return true;
    }
};

/* Example with typedefs within the traits class */
#include <type_traits>
template <typename T> // default implementation
struct MyTypeTrait {
    typedef T value_type;
};

// specification for pointers
template<typename T>
struct MyTypeTrait<T*> {
    typedef T value_type; // in case of pointers, we also receive the basic type of T back (not the pointer type)
};

// usage of the typedef - usage of traits classes are mostly done also with templates
template <typename T>
void ProcessData(const T& data) {
    std::cout << "Processing data of type " << typeid(T).name() << std::endl;
}

int main() {
    // basic traits class
    someFunction<int>();    // Ausgabe: Type T is arithmetic.
    someFunction<double>(); // Ausgabe: Type T is not arithmetic.
    
    // traits class with method
    if (MyTraits<MyClass>::hasSpecialFeature()) {
        std::cout << "Specific method called" << std::endl;
    } else {
        std::cout << "Common behaviour for MyClass" << std::endl;
    }
    if (MyTraits<int>::hasSpecialFeature()) {
        std::cout << "Common behaviour for int" << std::endl;
    } else {
        std::cout << "Common behaviour for int" << std::endl;
    }

    // traits class with typedef
    int a = 42;
    double b = 3.14;
    int* pa = &a;
    double* pb = &b;
    // normal datatypes
    ProcessData<int>(a);
    ProcessData<double>(b);
    // pointer types
    ProcessData<int*>(pa);
    ProcessData<double*>(pb);
    
    return 0;
}