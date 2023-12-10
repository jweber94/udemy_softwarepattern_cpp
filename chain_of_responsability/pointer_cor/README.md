# Pointer Chain of Responsability
+ The idea is to implement a singly linked list to which we can add elements and have the possability to walk through the list and invoke individual methods
	- On top of the linked list implementation, we hold the reference to an class/instance that should get modifyed by the COR
+ The main difference between the common linked list implementation and the chain of responsability is that we work with inheritance
	- By defining a default behaviour (simple walk through without anything to execute specifically) via a virtual method (*not* a pure virtual), we ensure that all chain elements are considered.
	- The concrete modifyers are used to define behaviour which should happen with the instance that the COR should be modifying