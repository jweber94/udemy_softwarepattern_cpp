# Iterator design pattern
+ ***How to traverse datastructures - the iterator is the object that is responsable for having access to a traversing functionallity***
+ Iterators are a core functionallity of STL data containers
	- An iterator has the following properties
		* It keeps a reference to the current element of the underlying datastructure
		* It knows how to move from the current to the next element within the datastructure
	- Iterators can be used explicitly or implicitly (e.g. within range based for loops)
+ ***An iterator is an object that facilitates the traversal of a datastructure***