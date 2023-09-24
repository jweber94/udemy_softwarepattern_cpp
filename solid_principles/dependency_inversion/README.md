# Dependency Inversion Principle
+ Basic Idea:
    - 1.: High level modules should not depend on low level modules
    - 2.: Abstractions should not depend on details, instead details should depend on abstractions
    - 3.: High and low level modules should depend on abstractions to make their coupleing independend of detail implementations
+ This is the contrast to dependency injection
+ The handed over interface should be enough to use an instance in a higher level module while hiding the concrete implementation such that the low level module can be changed without changing the API/interface
    - To make this work properly, we incooperate the polymorphism property of C++
        - See the good example for more details

## Some general thoughts
+ Abstractions are:
    - Interface classes
    - Base classes
+ ***If we have direct dependencies from the low level modules within high level modules, the high level module is always affected by changes to the low level module, if we change datastructures or renaming some variables or methods!***

## Common implementation details
+ ***If we want to handover an instance to the constructor (or a setter function) of a class that we need to use in another class, we want to do this via a reference to an interface or base class instead of handing over an instance/reference to an instance!***