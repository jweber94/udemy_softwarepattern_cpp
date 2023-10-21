# Observer and Dependencies
+ If we have dependend properties (in our example _field_name_) that impacts other properties, we have a chain of dependencies that need to be travsered if one property has changed
	- This makes our code messe if we have too much dependend properties that can invoke events
+ The problem of dependend properties in observables need to be fixed at the observable implementation level and *NOT* at the base class implementation level
	- You might use other patterns or algorithms for traversing the property dependency chain

## Basics to more events then just one
+ If you implement more then just one event type, you can have different subscription lists or different callbacks to respond to events from the observables
	- This might help you with regard to the encapsulation of event callbacks