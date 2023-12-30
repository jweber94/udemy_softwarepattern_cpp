# Dynamic Strategy
+ Being able to change the behaviour of our high level object at runtime by exchanging its low level component via method calls

## Application example
+ We want to print a list in different computer text formats
	- markdown: We have to put a * in front of every list item
	- html: We need to implement something that adds the opening and closing tags for an unordered list (`<ul>...</ul>`) and the list item specifyers themself (`<li>This is our list element</li>`)

## Implementation Details
+ We are using the Interface Segregation Principle (ISP):
	- The ISP (developed by Robert C. Martin/Uncle Bob) says that an interface class should not force a derived class to implement methods which are not needed to allow the class to properly function
		* If we need to overload unused code for a derived class, the interface should be separated to fulfill the single responsability principle
	- In this example, we use the ISP in a very clever way:
		* The html printer needs the `start()` and `end()` methods of the `ListStrategy` class but the markdown parser does not need them. To avoid forcing the markdown printer to overload the `start()` and `end()` methods, we marked them in the `ListStrategy` as virtual but deliver an empty implementation for them, so the markdown printer does not need to overload them and they do not affect the result, since we have an implementation within the interface class.