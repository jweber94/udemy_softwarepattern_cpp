# Acyclic Visitor
+ This is ***not*** a pattern of the gang of four!
+ It relys on RTTI ([Run-Time Type Information](https://www.geeksforgeeks.org/rtti-run-time-type-information-in-cpp/))
	- Therefore it is not good regarding runtime execution
+ We implement a visitor pattern but with more flexability
	- By using inheritance and having base classes that catch unimplemented visit overloads, we can define which visitors should be executed and which should not
+ The accptance check is implemented within each individual visitable