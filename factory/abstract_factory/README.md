# Abstract Factory
+ This is the second approach to factories according to the gang of four
    - The examples before (factory method, concrete factory and inner factory) are just embodiments of the factory method pattern that is defined by the gang of four

## Basic Idea
+ We want to create instances of derived classes of an interface/base class via (derived-) class individual factory classes
+ We define an interface for the factorys that should be used to create the derived instances which needs to be implemented to create a corresponding factory
    - Therefor we receive a basic class interface for the factories that we can put into an arbitrary datastructure for manageing them
        * In our example this is a `std::map<Drinks, std::unique_ptr<HotDrinksFactory>>` so we can access them more easily