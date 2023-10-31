# Dynamic Decorator
+ We can build decorators for existing (maybe abstract) base classes and apply them to all derived classes to enhance their functionallity
 
 ## Advantages
 + We can decorate objects at runtime
    - We do not need to know how many and what exact object is used to get decorated
    - e.g. if we allocate objects that should get decorated via user input or via heap allocation
    - ***Because of this property, this decorator type is called a dynamic decorator***

## Disadvantages
+ We can ne access members of the dervied classes (methods or member variables) from the decorated object
    - Because the decoration class inherits also just from the base class --> we need to define a good interface to work with the decorated objects
    - Or we need to save the individual derived classes to use their API in parallel to the decorated object
+ In our example, the base class could not be as concrete as needed to have a valid interface that can manipulate the individual dervied class instances