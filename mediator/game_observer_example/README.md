# Game Mediator Example
+ In this example, the communication between the objects is done with an observer pattern, implemented with `boost::signals2`!
	- The mediator has is common task, which is to deliver a communication mechanism. This is done by being able to fire events.
	- The events are triggered by the objects that connect to the mediator (which is in this case, just by holding the reference to the game object)
		* The API for fireing the is events is implemented by `boost::signals2`