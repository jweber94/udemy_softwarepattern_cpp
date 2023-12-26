# Mediator Example ChatRoom
+ We have a central component which acts as our mediator. In this example it is the ChatRoom struct.
	- Every communication of the participants of the system (in this example the ChatRoom) ***will go through the mediators function to communicate***!
		* The components (aka users) do not communicate directly with each other!
	- The only possability to communicate directly is to know the ID of another person and sending a private message (`pm(...)`) via the mediator.
		* This requires the knowlage of the *ID*, but the components do not have a direct reference to each other
			- We have some kind of message passing implemented within the mediator!