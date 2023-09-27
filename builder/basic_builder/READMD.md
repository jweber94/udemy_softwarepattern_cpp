# Basic Builder Example
+ We want to structure the creation of an HTML element into a class (which is responsable to hold and format the data of the HTML element according to the single responsability principle)
+ The complex and successive creation of a HTML element needs to be abstracted via the builder pattern (i.e. to add childs to the root node and *we need to ensure we have a root node before we add children!*)
	- In this example done via the constructor

## Main Takeaway
+ Most of the time, the builder delivers an API for interacting indirectly with the underlying instance. The user of this (builder-) doesn't have access to acutal datastructure. Instead it is possible to interact with it via a defined (and therefore testable and controllable) API!
	- In order to do this, we make use of an object oriented implementation approach
