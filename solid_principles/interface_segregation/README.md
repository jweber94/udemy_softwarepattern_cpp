# Interface Segregation Principle
+ ***Principle is only regarded to interface implementations!!!***
+ Aim:
    - ***Do not create interfaces that are too large***
        - Avoid to require the implementer of the interface to implement unneeded stuff
    - "_Segragate interface definitions to NOT force the programmer to implement unneeded interface methods_"
        * E.g. if we differentiate classes from an interface that do not need to use *all* interface methods within the application logic, we should split them up into multiple interfaces and do multiple inheritance instead of inheriting from one extensive interface class which contains all possabilities.
+ The principle also avoids confusion by the user of the API which is implemented by the interface definition, since not implemented functions that printout logs or throw exceptions that a method is not implemented might be noticed only after the code is already in production
    - Main Advantages:
        * Avoid unnecessary implementation effort
        * Make the API for a class that is derived from the interface more clear
+ Segragation translated to german: _Aufteilung_
+ Realization:
    - Break up interfaces into smaller, logical related interfaces
    - Avoid defining too big interfaces

## Composeing segragated interfaces to more complex interface definitions (and classes)
+ We can compose multiple interfaces to a _super_-interface by multiple inheritance
+ If we want to implement a class from a composed interface, we can build a decorator class around the sub-classes
    - Make the multiple inherited classes from the interface members of the derived class from the _super_-interface class by reference
        * The sub-class instances need to be handed over by the constructor
    - Call the methods of the members interface-references in order to implement the methods from the _super_-interface