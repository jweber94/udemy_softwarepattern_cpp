# Interpreter Design Pattern
+ ***An interpreter is a component that processes structured text data. Does so by turning it into separate lexical tokens (= lexing) and then interpreting sequences of said tokens (= parsing)***
	- An interpreter consists of
		* A lexer (tokenizer)
		* A parser (converts tokens to objects in our code)
+ Interpreter development is a separat branch of computer science
	- Broad field with a lot of special cases and details. We could do a complete course on interpreter design.
+ Interpreters are everywhere within our computer, e.g. python interpreter, command line parsers, office programms, compilers, HTML parsers within the browser, REGEX, ...
	- all applications that works with text directly or under the hood, which is basically every application to some extend!

## Properties of interpreters
+ An interpreter got a textual input that needs to be processed by the interpreter
	- Commonly, text is processed and turned/projected into some kind of object oriented datastructure within our interpreter application to be able to work with it!
+ Most of the time, a state machine is running under the hood to check which text building block can be converted to which class instance within our interpreter program