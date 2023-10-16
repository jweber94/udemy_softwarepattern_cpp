# Bridge Design Pattern
+ Main purpose: ***Connecting components together through abstractions***
	- It is kinda like dependency injection with interfaces like we had before
	- It avoids the "Cartesian Product complexity explosion - that means we receive a much higher order tensor if we calculate the cartesian product of two lower order tensors tensors (e.g. two vectors with three elements result in a matrix that has 3x3 = 9 elements)
+ ***A bridge is a mechanism that decouples an interface (hirachy) from an implementation***
	- And therefore we do not rely so much on inheritance if we have more complex inheritance structures
	- To use this in a useful way, we have to cluster the inheritance hirachy that we still need for our software architecture and the parts that could get abstracted by the bridge and thereby minimize the implementation effort!
	- Example:
		* Inheritance Hirachy plus aggregation:
```
Thread Scheduler (abstract base class - contains methods to Windows and Linux Scheduling methods)
	* Preemptive Scheduler (inherits from Thread Scheduler)
		- Some preemtive specific stuff
		- Windows Implementation of the Preemptive Scheduler (override methods from the base class)
		- Linux Implementation of the Preemptive Scheduler (override methods from the base class)
	* Cooperative Scheduler (inherits from Thread Scheduler)
		- Some cooperative specific stuff
		- Windows Implementation of the Preemptive Scheduler (override methods from the base class)
		- Linux Implementation of the Preemptive Scheduler (override methods from the base class)
```
		* Restructured Hirachy:
```
IOSSchedulingSpec
	- Pure Virtual Methods that implement common functionallities to interact with the plattform specific scheduler

LinuxSchedulerSpec : public IOSSchedulingSpec
	- Linux Implementation for the Scheduler interaction - pure virtual of IOSSchedulingSpec gets overwritten

WindowsSchedulerSpec : public IOSSchedulingSpec
	- Windows Implementation for Scheduler - pure virtual of IOSSchedulingSpec gets overwritten

Thread Scheduler
	* Preemtive Scheduler
		- Preemptive specific code
		- Uses ImplToOSScheduling for interacting with the (plattform agnostic) Scheduler interface
	* Cooperative Scheduler
		- Cooperative specific code
		- Uses ImplToOSScheduling for interacting with the (plattform agnostic) Scheduler interface
	* ImplToOSScheduling (IOSSchedulingSpec*)
```
		* By restructuring the code like this, we have the plattform dependend implementation of the interaction with the plattform specific schedulers just one time and not for every Scheduling class individually
			- That means if we decide to implement another scheduling scheme in the future or to port our code to another plattform (e.g. FreeRTOS) in the future, we don't have to rewrite the interaction classes again. We just need to extend the needed functionallity without reimplementing the same stuff over and over again
		* ***That makes our code base much more scalable*** then implementing the complete inheritance structure every time again!

## Common Use Case
+ If we want to have the same functionallity on different target APIs
+ If we want to hide implementation details from the user of a client (mostly done if you sell libraries commerically)

## Common implementation
+ Mostly done by handing over references to interfaces of the implementations
	- Therefore a brige is a combination of dependency injection combined with abstract base classes
+ Sometimes a pimpl idiom is used to vary implementations without the need to recompile and in order to hide concrete implementations from the user of an API (mostly done if you build and sell a library but you do not want the customer to have the full source code)
+ If you insert an abstaction by reference, you are building a bridge