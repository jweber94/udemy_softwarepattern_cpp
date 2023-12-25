# Basic explaination of C++20 Coroutines (especially co_yield)
+ The role of `co_yield` in functions/methods:
	- co_yield is some kind of an alternative to the `return` statement in normal (non-coroutine) functions.
		- If we have multiple `co_yield` statements within our function, the first co_yield that is encountered will return a value to the function caller
			* If we then call the method another time, the method will resume right after the first encountered `co_yield`!
	- By implementing this functionallity it is possible to safe the state of a function/method and getting in between value from it back!
+ ***By using `co_yield`, we can have the coroutine (aka the function within which the `co_yield` statement is implemented) return values incrementally while maintaining its (the function/methods) state and continuing as needed (when the next call to the function/method comes within our application logic).***
	- So we can store the state of execution and returning back to it in the future.
	- But the execution of our basic program is still in a sequential order! We do *not* implement a concurrent program just by using `co_yield`!

## The generator class
+ The `generator<T>` is a so-called _Promise_ object and helps to facilitate the interaction between the coroutine and the calling code.
	- It is the needed return type, if we use a `co_yield` statement instead of `return` in our function/method. (So if we want to use a coroutine in our code)
	- In combination with a function that uses `co_yield`, it acts kinda like an iterable object. (even if it isn't one under the hood (since it is a differenciation of a promise))