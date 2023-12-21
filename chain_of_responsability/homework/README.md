# Learnings from the homework
+ We need to store the returned value after a query to the system within the query object - *never* modify the base values since these are the baseline if a modifyer object is removed from the system
+ We can use a separate object to hold all instances that affect the COR dependend object
+ It is better to use a query method with inheritance and utilize polymorphism to implement the COR instead of the basic pointer implementation with a singely linked list
	- A nicer example can be seen within the `./alternative_solution/alternative_cor_homework_solution.cpp`