# Deep Copies
+ To make the derivation from a prototype possible, we need to enable a deep copy by implementing the copy constructor as well as the copy assignment operator!
    - If we don't do this, we will generate unexpected behaviour, since the derived instances can write to the (copied) pointer address of the prototype instance!
    - Or the prototypes address gets deleted/invalidated and the derived instance writes to an undefined/unreserved memory address which can lead to very bad memory issues!
+ The possability to create deep copies of classes is the basis for implementing a prototype.
    - To realize the prototype pattern, we just need to instanciate a prototype and implement the copy constructor as well as the copy assignment operator (to make the use of the class more convenient and the code less cumbersome)
    - But if you want to make use of the full potential, we need to enhance the basic implementation requirements with e.g. a factory to create derived instances of the prototype