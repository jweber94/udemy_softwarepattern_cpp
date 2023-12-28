# State Machine
+ Most objects have the state as a field of them anyway
	- But the design pattern is a linkage between the state/state transition and some function executions!
		* Therefor, the state design pattern is a behavioural pattern!
+ Changes of the state of an object can happen by calling methods of the object (= explicit state transition) or by listening to an external event (e.g. by using an observer pattern) in an implicit manner!
+ ***The State design pattern is a pattern in which the objects behaviour is determined by its state. An object transition from one state to another (something needs to trigger a transition). A formalized construct which manages state and transition is called a state machine.***