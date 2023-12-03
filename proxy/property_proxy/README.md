# Property Proxy
+ Other programming languages have the property type built-in. We can implement it on our own in C++ by implementing a property proxy.
+ ***A Property***: Is a field/variable plus a getter and a setter for that field.
	- _But we do not want to have explicit getters and setters. Instead we want fields of a class act like normal fields while having additional functionallity._ (e.g. checking values before using getters and setters)