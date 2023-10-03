# Prototypes
_Are a partially or fully initialized object/instance that you copy/clone and make use of to create new instances of the class of the object/instance_
## Motivation and basic Idea
+ Like in hardware development, sometimes it easier to create new differenciations of classes from an already existing one instead of creating it from scratch.
    - ***That means we take an already created instance, copy its properties and adjust the relevant members so that we obtain the targeted configuration without initializing everything new from scratch.***
+ The already created instance from which a new instance is derived is called the ***prototype*** from now on
+ We want to _reiterate_ on the prototype to adjust the properties for our application
    - We create variations of the prototype

## Implementation
+ We need to do deep copies in case the prototype contains pointers or references as members to avoid overwriting the prototypes properties
+ In C++ we need the Copy-Constructor as well as the Copy-Assignment Operator to be implemented for the class that is used as the prototype/for the class that should get instanciated via a prototype instance
+ We need to make the cloning of the prototype instance as convenient as possible, e.g. via a factory which contains the prototype as member

## Application Use Cases
+ ***If we have a very complicated constructed instance (i.e. via a long and complex constructor or a specific call sequence of a builder) that needs to be instanciated multiple times with slight variations of a few of the parameters/constructor/builder arguments***
    - Whenever we call the same complex constructor multiple times, we should consider a prototype!