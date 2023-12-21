# Command Design Pattern
+ The command design pattern is a behavioural design pattern
+ Normal C++ field/variable/member assignments are perishable
	- We cannot undo an operation/property assignment
	- We also cannot directly serialize a sequence of actions (calls)
		- That means, we can serialize the Command Objects (= the command design pattern), send it via the network and deserialize it on a different process/machine to use it there. This might be an interesting szenario for me.
+ ***A command is an object which represents an instruction to perform a particular action. Contains all information necessary for the action to be taken.***

## Command Query Separation
+ Difference between commands and querys:
	- Command:
		* A command is the ask for an action/change on a mutable object. (e.g. _dear object X, please set your field value Y to value Z_)
	- Query:
		* A query is the ask for a property/field value of an object.
		* Querys do not execute a change of the object
+ The command query separation (CQS) is a concept where we separate programmatically the sending of commands and query to an object!
	- The implementation is for both (commands and querys on objects) the same regarding the design pattern. In the gang of four book, both are described as the command design pattern, even if the functional meaning of commands are broken by the name of the pattern since you implement querys in the same way.
