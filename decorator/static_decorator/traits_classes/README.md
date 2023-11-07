# Traits Classes
+ Traits classes are template based classes which have `static const ...` members that can be overwritten by specializations of the relevant template
    - Alternativly these members can be typedefs
+ ***The basic idea is to have more information about the class at compile time (since they have static members, these are known in advance before you compile your programm)***
    - Therefore, the compiler can check against these variables, which can help to optimize the execution time and is able to check for compilation problems

## Implementation of Traits Classes
+ Important note: `static const` variables are known at compile time! Keep this in mind when implementing or working with traits classes
+ As said before, traits classes are based on the template specialization mechanism of C++.
+ The idea is to define a template based class which has one or more `static const` members (or methods) which define the default behaviour of the traits class.
    - Then you can specialize an implementation for a specific template argument which overwrites (aka has its own implementation, which is the technically more correct description) the default implementation for this specific template argument
+ Template specifications are always compiled, no matter if they are actually used or not
    - That means you can implement them within a library and they are available in a project that uses the library even if they not part of the code that is called from the application
+ See the example code for more details

## Important details on traits classes
+ By convention/usually, traits classes are only defined by `static const` members. Normally they do not have methods, even if it would be possible
    - This is an antipattern, since it might confuse other programmers

## Use cases of traits classes
+ Compile time optimizations
    - E.g. the size of memory that needs to be allocated can be determined by the traits class at compile time which enables us to use stack memory instead of heap memory (which would not be possible if we do not use traits classes)
+ Serialization techniques
    - Depending on the class, the traits class can be used as a switch for different serialization algorithms
+ Type traits, e.g. in concepts
+ Control the behaviour of other template based classes or functions
    - We can know at compile time, to what specification a traits class will be translated. Therefore, we can control which branches of our programm will be executed and therefore needed to be compiled
        - This is partly what the more efficient code is about, if you are using traits classes
        - This is the `_is_arithmetic_trait` example in the code is doing
+ Also `typedef`s can be done within traits classes to have them available within other definitions

## Traits classes from the STL
+ There are some traits classes within the STL that can be used in your code
    - These are defined within the header `#include <type_traits>`
+ Most commonly used traits are:
```
    std::is_integral: Überprüft, ob ein Typ eine ganze Zahl ist.
    std::is_floating_point: Überprüft, ob ein Typ ein Fließkommazahlentyp ist.
    std::is_array: Überprüft, ob ein Typ ein Array ist.
    std::is_pointer: Überprüft, ob ein Typ ein Zeiger ist.
    std::is_reference: Überprüft, ob ein Typ eine Referenz ist.
    std::is_enum: Überprüft, ob ein Typ ein Enumerationstyp ist.
    std::is_class: Überprüft, ob ein Typ eine Klassentyp ist.
    std::is_function: Überprüft, ob ein Typ ein Funktionszeiger ist.
    std::is_same: Überprüft, ob zwei Typen identisch sind.
    std::is_base_of: Überprüft, ob eine Klasse eine andere Klasse abgeleitet ist.
    std::is_convertible: Überprüft, ob ein Typ in einen anderen Typ konvertiert werden kann.
    std::is_empty: Überprüft, ob eine Klasse leer (keine Datenmitglieder) ist.
    std::is_union: Überprüft, ob ein Typ eine Vereinigung ist.
    std::is_trivial: Überprüft, ob ein Typ ein trivialer Typ ist.
    std::is_pod: Überprüft, ob ein Typ ein Plain Old Data (POD) ist.
    std::is_arithmetic: Überprüft, ob ein Typ ein arithmetischer Typ (int, float, usw.) ist.
    std::is_member_function_pointer: Überprüft, ob ein Typ ein Memberfunktionszeiger ist.
    std::is_member_object_pointer: Überprüft, ob ein Typ ein Memberdatenzeiger ist.
```