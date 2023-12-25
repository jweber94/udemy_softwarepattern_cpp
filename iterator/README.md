# Iterator design pattern
+ ***How to traverse datastructures - the iterator is the object that is responsable for having access to a traversing functionallity***
+ Iterators are a core functionallity of STL data containers
	- An iterator has the following properties
		* It keeps a reference to the current element of the underlying datastructure
		* It knows how to move from the current to the next element within the datastructure
	- Iterators can be used explicitly or implicitly (e.g. within range based for loops)
+ ***An iterator is an object that facilitates the traversal of a datastructure***

## Basic Assumptions
+ An object can be iterated/traversed if a `begin()` and `end()` pair is defined
+ The iterator object defines, how to traverse the object
	- Therefor, we can have multiple iterators for different traversing strategies
+ The bare minimum is to implement the `!=` and `++` operators for the iterator type (which needs to be associated with the datastructure/class that it should traverse)