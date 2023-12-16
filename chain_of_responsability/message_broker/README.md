# Message Broker Design Pattern
+ The event broker is a combination of the design patterns:
	- Observer-Pattern
	- Chain of Responsability
	- Command Query Separation
	- Mediator Pattern

## Basic Idea
+ The Game object is the mediator that connects query objects with instance objects within the game by working as an observable (implemented with `boost::signals2`)
+ The instance objects hold the basic value (for attack and defence) and ask the game object for their member access (attack and defence) since these depend on modifyer objects that might be present within the game
+ The Modifyer objects connect to the signal member of the game and link a lambda to them which modifys values of the instances within the game whenever they are requested
+ The Query instance holds the modifyer adjusted values of the requested value
+ The main part of this message broker design is that the getter will return the adjusted value from the query object instead of returning the locally hold base value of the Creature instance