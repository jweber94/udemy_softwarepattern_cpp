# Handmade interpreter
+ This is very simple example for a parser that is able to evaluate basic numeric expressions with plus and minus operations!
+ The code is separated into two parts:
	- The Lexer: Extract the individual components from the input string into objects that tells us which to kind of object we need to convert them and safe the corresponding raw data to them
	- The Parser: Go through all extracted tokens and creature actually usable objects from them. This requires the interpretation of the data in combination with the determined type from the lexer
