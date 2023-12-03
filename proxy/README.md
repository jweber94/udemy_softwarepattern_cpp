# Proxy
+ A proxy is an interface/API for accessing a particular resource
+ The proxy has a stable interface/API but the underlying object can have ***completly different*** behaviour
+ Definiton: ***A proxy is a class that functions as an interface to a particular resource. That resource may be remote, expensive to construct, or may require logging or some other added functionallity***
+ _A proxy is changeing the behaviour of and object that everybody uses but preserve the API_

## Motivation
+ Proxys are a common pattern, if you want to have functionallity either on the process where the proxy is implemented or the functionallity is executed on a separate process and is then transferred to the proxy object on the local process
	- This is an example for the _communication proxy_
+ There are multiple kinds of proxys
+ Most of the time, the proxy (in case that it lives on the same machine), the proxy object enhances the basic functionallity of the underlying object with some convenience functions

## Basics
+ A proxy has the same interface as the underlying object. It is some kind of transparent layer on top with regard to the API
+ Member-Methods are redefined to the original object. Therefore their behaviour can be enhanced

## Differences between proxys and decorators
+ ***The proxy preserves the interface of the underlying object while the decorator enhances the interface***
	- Therefore the user of the proxy does not need to change his code besides another datatype for instanciation
+ Decorators typically aggregates/references the object that it is decorating
+ The proxy does not need to instanciate the basic object. It can have completly different behaviour
	- E.g. if you instanciate a proxy that invokes executions on different processes/machines via network communication
+ *Be careful*: Some proxys might enhance the API a little bit by enableing you to access the under the interface lying object. E.g.if you have a smartpointer (which is a proxy for raw pointers), you can access the raw pointer by calling `mySmartPtr.get()`. This is a slight enhancement of the API of `mySmartPtr`.
