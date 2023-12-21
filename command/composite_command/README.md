# Composite and Command
+ Macros in MS Office:
	- This is a sequence of commands, one after another and we are able to reexecute or undo them in a reverse order (if they were invoked before)
	- We can also playback them in reverse order
+ We want some objects that have `call()` and `undo()` commands which realize the application of a sequence of commands in normal or reverse order!
	- This is the idea of the _composite_ design pattern, which we mix with the command design pattern from this chapter!
	- So we implement a combination of the composite and the command design pattern for this example
## Implementation Details
+ ***The command objects are just a wrapper for the Arguments of a member method with the possability to implement interdependencies between method calls!***
	- This is in my opinion the essence of the command design pattern
	- We also can serialize the command objects more easily then to have just the method parameters on their own (e.g. if we want to transfer them via the network)