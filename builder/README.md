# Builder Pattern
+ Is a ***creational design pattern***
+ Used, when the construction of an instance of a class gets complex if you do it via the constructor
	- We want to have a simple API to construct instances
	- We want to do piecewise construction
+ A builder is commonly a separate class thats purpose is to construct the actual instance via a simple API

## Basic Idea
+ ***When piecewise object construction is complicated, provide an API for doing it succinctly***
+ We want to use object oriented programming in order to create a complex instance structure via an easy API
+ After we created the instance via the builder, we want to have access to the constructed instance via its class, *NOT* via the builder API!
	- We can use it after the initial construction but we might not want to be forced to have only indirect access to the instance!
		* Therefore we must enable the user via an operator or a build function or something else to get the instance out of the builder

## Main challenges
+ Force the user to construct an instance only via the builder API
+ Enable the user to access the instance without the builder after it is constructed
+ Make an easy to use API