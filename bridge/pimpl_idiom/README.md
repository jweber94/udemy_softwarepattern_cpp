# Pimpl Idiom
+ The pimpl idiom is a manifestation of the brige design pattern with the purpose of hiding implementations from the consumer of a library
	- i.e. handing over the headers and the binary but not the actual `.cpp`s which contain the interlectual property of the library creator

## Implementation Details
+ We need to forward declare the implementation class of our API class to be able to create a pointer to it within the actual API class declaration
+ If you use a pimpl idiom, you never implement definitons of methods within the header!
	- Because you want explicitly hide implementation details from the user of your API class
	- And you do not have access to the implementation class within the header, since it is not defined there yet!
+ The pimple idiom is one of the rare applications where you write a class declatation (and definition) (of the implementation class) within a `.cpp` file!

## Benefits
+ Hide interlectual property if you sell your library
	- Hide the inner mechanics of your library implementation
	- And thereby hide the underlying software structure (especially names of the methods) of the implementation class
+ Speedup compilation
	- You don't need to recompile your application if you get a new binary for your pimpl since it links only to a different implementation within the binary and not to a complete other code (via the indirection with the pointer)