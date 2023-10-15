# Basic Adapter
+ To implement an adapter, we need to identify how the given API looks like and how our targeted API is defined
	- Then we need to create an adapter class or struct which converts the result of the one API the the input format of the other API
		* ***We might need to calculate the conversion if no direct remapping is sufficient!***

## Implementation Details
+ We need to implement a class that is instanciated by the result of the given API
+ We feed the targeted API with method calls to our instance of the adapter
