# Memento
+ Synonyms are _token_ or _snapshot_ for the state of an object/class/struct
	- With this memento object, we are able to recover object states 
	- All changes to the state of an object (via a method) will return an memento, which can be stored and applyed by the caller of the method in order to return the state which was created by the method from which it was returned.
		* So we can roll back the state of our object to the state to which the memento was created
+ You can go back to discrete points in time of the state history of an object
+ ***A memento is a token/handle representing the system state. Lets us roll back to the state when the token was generated. May or may not directly expose state information.***
+ If your object state is sufficiently small with regard to memory, you can store all mementos that are generated from a particular object and then implementing `undo()` and `redo()` methods on the object itself
	- This way we can navigate through all state changes of our object that has mementos and the complete memento history safed within it
 
## Implementation Details
+ Commonly a memento does not allow the user to see what state is stored in it. It also does NEVER allow to modify the state. Therefore, a memento typically has no accessor methods to the state information that it describes
	- Only this way we can be sure that we restore a valid, actually happened old state of our object from which the memento has stored the state
+ A memento is always customized to the object of which it should take a snapshot/store its state. Therefore, it is always associated with a specific class. To have access to private (state) members of the class that the memento should take a snapshot of, we can either set the targeted class as a friend of the memento or we implement the memento as a subclass of the class that it should store