# Factory
+ A (concrete) factory is not part of the book that is made by the gang of four
    - The gang of four defines the factory method and the abstract factory!
+ The idea behind the factory is to enhance the approach of the factory method pattern to fulfill the single responsability principle better
    - Therefore we have the class definition which is responsible to store and manage the data that is associated with it
    - And a factory class that is solely responsible for createing instances of that class
+ CAUTION: Since we need to mark the factory as a friend of the actual class that we want to create, we break the open-close principle