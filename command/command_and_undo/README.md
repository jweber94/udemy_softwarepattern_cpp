# Command and Undo operation
## Tipps and Tricks
+ Be careful with commands that have an `undo()` operation:
	- Think about historizing - is the command stateless or do we need to take previously executed commands (failed or not failed) into account?
	- Is the `call()` and `undo()` operation symetric or do we need to add additional logic in order to revert the changes made by the `call()` to the command object?
	- Most likly, we can only `undo()` commands in the reverse order that we applyed them
+ Be careful not to break the open close principle
	- Think carefully where to store the information if a `call()` was succeeded or not and where to store ordering of already executed commands