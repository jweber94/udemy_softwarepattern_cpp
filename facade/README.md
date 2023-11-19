# Facade
+ Basic Idea: ***Exposeing serveral components through a single interface***
	- And therefore make the use of serveral classes combined convenient to use for the API consumer
+ You can hide implementation details (maybe poorly designed software architecture) under the hood and combine them to a well thought through API design, which is the facade itself
	- You might enable the user of the facade API to access the underlying software layers (e.g. if you want to enable power users to have more control over the system)
		* *Therefore, think carefully what you want to expose from the underlying library to let powerusers make very specific adjustments which are not convered or fixed with your defined API*
+ ***The facade provides a simple, easy to understand/user interface over a large and sophisticated body of code***
	- _Take complex initializations/structures and stick them to a method that abstracts this complexitiy away and thereby makeing it easy to use_

## Common Application
+ We have a complicated API and need to do a lot to do a basic task (e.g. adding a node to a OPC UA with the open62541 library, adding columns to a viewport like in the video, ...)
	- The facade defines a new method (e.g. `add_node("name")` or `add_column("name")`) which hides the complicated creation from the API user and defines a simple to use interface for the individual purpose (*this is mostly needed due to the approach that libraries need to have a lot óf configuration possabilities but in your concrete application, you just want a very specific configuration all the time with just slight variations*)
+ If you don't create an API for a user, facades are created in refactoring efforts
 
## Implementation Details
+ We can utilize other design patterns to design our facade
	- Especially the creational patterns, like the builder, factory, singleton, ... in order to create complex types that are then easy to use via a properly defined API
+ The aim is to create the API that you are confident with

## Example
+ Console/Terminal: This is a very complex application, but we can open it up and write to it very easily with basic POSIX commands