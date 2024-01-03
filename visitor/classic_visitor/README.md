# Classic Visitor
+ We build our classic visitor approach by using a double dispatch mechanism
	- This is a workaround for staticly typed languages to have a runtime dispatching for base classes

## Implementation Details
+ Our visitor interface needs to know about all possible overloads and it enforces the implementation of these overloads within all derived visitor classes
+ The `accept` method needs to be overloaded and reimplemented (even if it is in all classes the same code) in all derived Expression (aka visitable) classes
	- This is due to the double dispatch approach, which is a workaround of dynamic dispatching in statically typed languages like C++ - see the DoubleExpression comment of the `visit()` method for more technical detail
+ In case of a depth first search tree traversion like in our example, we hand over the visitor class as a `this` pointer within the visit methods, if we reference another visitable/expression class, see the overloads of the `visit` method of `AdditionExpression` and `SubtractionExpression`