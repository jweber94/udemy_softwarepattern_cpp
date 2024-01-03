# Visitor Design Pattern
+ ***A visitor is a design pattern where a component (visitor) is allowed to traverse the entire inheritance hirachy. Implemented by propagating a single `visit()` method throughout the entire hierarchy.***

## Implementation Approach
+ We want to avoid type checks (but we can not avoid it completely)
	- We need to reflect the type of an object (what child class it is or if it is the base class), which leads to the usage of RTTI (Run-Time Type Information - https://www.geeksforgeeks.org/rtti-run-time-type-information-in-cpp/), e.g. via `dynamic_cast`
		* Caution: This is very expensive regarding runtime execution performance
+ To fulfill the open-close principle, we need only to implement an `accept()` method for the visitor class and from then onwards, we can define our visitors (which enhance the functionallity of all targeted classes) without editing the existing code.
	- Which is the main principle to have reusable code: We do not want to test already tested code just because we implement a new feature! (open-close principle)
	- And it supports the single-responsability principle
