# Fluent Builder

## Fluent Interfaces/APIs
+ A fluent API is the possability to chain methods on objects!
+ Example:
```
HtmlBuilder htmlBuilder("ul")
htmlBuilder.add_child("li", "Foo").add_child("li", "Bar")
```
+ This is ***not*** specific to the builder pattern!
	- But we learn it within this context
	- Fluent interfaces are a common implementation variation in order to create clean and easy to use APIs

## Considerations
+ ***Give a hint to the API user that he should use the builder instead of the concrete class***
	- Implement a static `::build()` function on the class that is complicated to build (aka the class for that we have implemented the builder)
+ ***Force the user to use the Builder instead of operating on the constructed element***
	- Done via classes with private and public constructors
	- Make the constructors of the complex constructed class private via a class definition
		- Add a static (since we have no instance to operate on) `build()` method/function on that class
			- This will lead the user of the class to the corresponding class constructor
	==> By doing this, we enforce a specific creation workflow via the builder which cannot be worked around
	- Makeing a clean API: We want to hide the managed instance from the builder by making it private via a class and then deliver a `build()` method that delivers the created instance so that the user does not stuck with the builder instance (and have access to its _easily constructed_ instance)
+ To make the builder able to use private members and methods of the class that should get created with it, we commonly use the `friend` keyword!
	- This is a very good example when the friend keyword is sensfully used!