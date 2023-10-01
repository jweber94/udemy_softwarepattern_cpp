# Factory
+ ***The factory design pattern is used to create a component that is soley used (single responsability principle) for the wholesale (not piecewise) creation of instances of a class!***
+ Factories are used if we want to create instances of a class in a single statement but using the constructor is to complicated so we want an API that is more flexible and more easy to use then a plain constructor
    - ***This is a good idea if we have a fixed amount of members that we need to initialize for a class (no `std::vector` etc is needed to be filled up during construction) but to construct the instance via a plain constructor is too complicated (i.e. needs more steps then just the initialization of the members or the member initialization is too complicated (i.e. too many optional parameters for the constructor are needed))*** 
+ There are two approaches to factories according to the gang of four:
    - ***Factory-Method Pattern***: Make the constructor of a class private and deliver static functions to create the instances of the class to have a stable and easy to use API
    - ***Abstract Factory***: This is an object oriented approach to factories
    - Factory method and factory share the same idea behind the pattern but the implementation approach is slightly different
## Use Cases
+ ***NOT*** if you need to do piecewise construction
    - We have a constructor like call in case of the factory
+ Commonly used if we have lots of different variaties to create an instance of the class  
+ Complicated instanciation
    - Too many modi via optional params --> optional parameter hell
    - Too many parameters
+ Name of the constructor/class is not descriptive enough that the user of the class/user of the API does not get what he needs to insert to the parameters to get a valid instance of the class
    - Then the factory(-method) is used to expose a more clearly explained (via parameter names and method names) API for the instanciation
