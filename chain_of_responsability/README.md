# Chain of Responsability
+ Main goal: ***Let a sequence of components process some information one after another***
+ The chain of responsability is a sequence of handlers that are used to process an event one after another
+ Within the programm, a chain (mostly a pointer chain in a singlely linked list or something like that) of event handlers is defined. Be careful: The order of the chain members are crucial to the correct functioning!
	- Every event handler/chain element is executed on the given data
	- Every chain element could decide to skip its execution on demand/input parameters
	- Every chain element could decide to stop the execution of the chain
+ By defining an order of handlers, we can ensure having all defined handlers applied to the event that was invoked

## Practical examples:
+ Responsability within a company: employee --> manager(s) --> CEO
+ Computer Card Game:
	- Cards could be boosted by other (attribute/event) cards

## Implementation details
+ Via singly linked lists that holds the pointers/references to the handlers of the event
+ Centralized list approach:
	- This is a holistic approach where the observer pattern is used to implement the decentralized list of handlers
+ Removing elements from the COR is (dependend on the datastructure) a little tricky

## Enhancements
+ Prioritize the list elements by using a different underlying datastructure (not a singly linked list, e.g. an ordered map where the order is determined by the priority)
