# Singleton
+ Singleton is one of the most controversial design pattern
    - Mostly a bad idea if you have the requirement of testable and extensible code!
+ It is a bad idea if our application logic is stronly coupled with the singleton.
    - We can avoid this by using an interface and realize dependency injection with it!
+ ***A singleton is a component which is instanciated only once!***

## When is it used?
+ If we want to have only one instance of an object
    - We need to reference always the same instance if we access it
    - E.g. object factory or if we have a very computationally expensive constructor for a class

## Implementation details
+ We need the have a method that returns a reference or a pointer to a static instance
+ We need to forbit the user to create additional copies of the instance
    - Therefore we need to forbit the 
        * copy constructor
        * copy assignment operator
        * constructor
+ We need to make the first (static) instanciation thread safe
    - That means we need to do a lazy instanciation
    - This is standart in C++11 and newer for static variables - we can not create multiple instance from different threads, if a method has a static declared variable in it --> we always create only one static instance
