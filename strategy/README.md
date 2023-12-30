# Strategy Design Pattern
+ ***The Strategy design pattern enables the exact behaviour of a system to be selected either at run-time (dynamic) or compile-time (static). The strategy design pattern is also known as a policy (especially in the C++ world)***
+ The strategy is also a behavioural design pattern
+ The strategy allows us to partially specify the behaviour of the software system at runtime (or compile time, depending on the implementation approach)
+ It is also know as _policy_ in other programming languages
+ Like the decorator design pattern, the strategy could be either static or dynamic
	- It is basically the same functionallity

## Thinking approach
+ Most algorithms can be decomposed into two parts:
	- A high level logic
	- And a low level execution
+ The strategy design pattern aims to implement reusable a high level algorithm with the possability to exchange the low level execution steps
	- And this is done with the use of inheritance implementationwise
