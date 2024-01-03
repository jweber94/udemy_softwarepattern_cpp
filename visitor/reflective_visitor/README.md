# Reflective Visitor
+ The reflective approach is the approach to make the *single responsability principle* work with the already discussed visitor approach.
	* We use the same example as before (the binary tree math expression printing)
+ The reflective approach is problematic in C++ (and other statically typed languages), since we have no type [reflection](https://en.wikipedia.org/wiki/Reflective_programming) nativly to the programming language
+	- To have some kind of _type reflection_, we use `dynamic_cast` to check if we can cast a pointer of the base class to a derived class or not

## Advantages and Disadvantages of the Reflective Visitor Approach
+ Advantages:
	- We fulfill the single responsability principle, since our `ExpressionPrinter` class is only responsible for the printing and the `DoubleExpression` as well as the `AdditionExpression` is responsible for the arithmetic definition of expressions
+ Disadvantages
	- We break the open-close principle since we need to edit the print dynamic dispatch with the reflective approach if we have new derived classes in our inheritance hirachy.
	- The dynamic_cast is costly at runtime but it is the only possability to have a dispatching of the base class `Expression` pointers at runtime
