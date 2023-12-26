# Mediator Pattern
+ ***The mediator pattern is a behavioural pattern***
+ The mediator is an object that facilitates the communication between components/other objects who do not know each other directly
	- This is helpful if components/objects can come in or go off the system at any time
		* If you link components directly together, you either need to implement a strickt checking of the validity and/or a register/unregister mechanism for *every object connection*, or you might try to access an already invalid object
		* In any case, direct linking is more complex to implement and more error prone!
	- Example: Chat rooms, Players in MMORPG
+ The mediator is a central component that facilitates the communication between all components within the system without the requirement to let all components know about each other
	- Therefore, the individual objects are losely coupled

## Summary of the properties of the mediator pattern
+ ***A mediator is a component that facilitates communication between other components without them necessarily being aware of each other or having direct (reference) access to each other.***
+ Implementationwise, a mediator is an object that all associated objects within the system can reference
	- The mediator delivers the functionallity for the communication between all objects!