# Composite Design Pattern
+ ***Main Goal:***: Treat single objects in the same way like conclumerates of these objects
	- Like in Powerpoint where you can group some geometric shapes to a collection of shapes that can be moved, scaled or deleted as a whole instead of doing it instance by instance
	- _Creating componds of objects and treat them in the same manner as individual objects_
	- We want to be able to call the same method (-name) on the compond of the objects as well as on the individual object but with similar (but either with regard to the group or with regard to the individual) behaviour
+ ***The Composite is a mechanism for treating individual (scalar) objects and compositions of these objects in a uniform manner!***
	- The composite and the individual object should have the same API!

## Implementation in C++
+ Make use of _simulated_ duck typing in C++
	- Via defining the `begin()` and `end()` for the individual objects/classes
	- CAUTION: This is no _real_ duck typing since C++ checks all types explicitly during compile time
	- The Idea behind _duck typing_ is: "If it looks like a duck, swims like a duck, quacks like a duck, then it is probanly a duck", which means that the type of an object is defined by its behaviour and not by its actual datatype
		* duck typing is a paradigm that is mostly used in interpreted languages like python or ruby
	- In C++ we can simulate duck typing by implementing the aforementioned begin and end methods and use range based algorithms
		* Thereby we masquerading scalars as collections of these objects
