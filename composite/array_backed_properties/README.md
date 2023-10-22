# Composite as Array Backed Properties Pattern
+ Array Backed Properties Pattern is a combination of the composite and proxy design pattern
+ The idea of the composite in this example is that we use the array as a common representation of the properties/fields so we can work with them by projecting the index via an enum to the array of these field exactly like accessing them direcly as individual members of the class
	- The enum projection is used under the hood. The consumer of the class API does not need to know about the array projection
	- ***This only works as long as the fields of the class have the same types!***