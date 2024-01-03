# Intrusive Visitor
+ The idea behind a intrusive visitor is that we enforce the implementation of a method for a class hirachy by defining it as *pure virtual* within their commonly used base class.
+ The base class is used within the class hirachy as method parameters and we call the visitor method from other derived classes within a derived class of the base class where the visitor method is defined
	* In this way, we are able to 
+ ***CAUTION: This kind of visitor is not recommended since it breaks the open close principle: We need to change all derived classes in a class hirachy to realize the new functionallity that comes with the visitor!***
	* Because of this, this approach is called the _íntrusive_ visitor approach