# Multimethods
+ ***Multiple dispatch – the selection of a function to be invoked based on the dynamic type of two or more arguments – is a solution to several classical problems in object-oriented programming.***
+ The presented example of multimethods is an example of how to fight the missing multiple (runtime) dispatch in a statically typed language like C++
+ The idea is to have some kind of combine-`accept` method instead of a plain accept method
	- e.g. if we can not traverse all visitables via handing over the `this` pointer of the subordinate `accept` of the members of the visiable (like the `AdditionExpression` with its `left` and `right` expression pointer) for whatever reason
+ A multimethod approach is a separate _kind of_ visitor approach - we do not implement it directly as an addon to a classical visitor pattern!

## Basic Implementation Idea
+ Doing the method dispatching like in the classic visitor example but with two arguments instead of one
	- We basically want to implement a _multiple dispatch_ mechanism
+ We implement a base class which uses CRTP ([Curriously Recurring Template Pattern](https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/)) to deduce a type information for all inheriting classes, so we are able to decide which method should be called at runtime depending on their type information

## Example Description
+ Collisions in space