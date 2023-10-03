# Serialization to avoid copy constructor implementations
+ The more complex the instance gets, the more complex the implementation of all copy constructors and copy assignment operators gets!
    - To avoid this, we can use serialization instead
+ We need to do this via serialization and deserialization because C++ does not implement the reflection functionallity (like it is in other programming languagles to deep copy an object hirachy)
+ The advantage over implementing all copy constructors is that we have to write much less code for the same functionallity

# Advantages
+ Less code then implementing the copy constructor
+ (De-)Serialization might be used later on in the development process
    - e.g. to save and be able to recover system states
+ If we do serialization with `boost::serialization`, boost forces us via the compiler to implement all serialization code correctly
    - Boost always do deep copies in case of pointers as members of classes that should get serialized (automatically)