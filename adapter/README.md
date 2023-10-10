# Adapter Pattern
+ The adapter is a ***structural pattern*** (in contrast to creational and behavioural pattern)
+ Main application:
    - _Getting the interface you want from the interface you have_

## Basic definition
+ ***An adapter is a con`struct`*** which adapts an existing interface *X* to conform to the required interface *Y*
    - Thereby the interface might need to implement some logic to transform a given datastructure to the desired datastructure (e.g. by calculating points from a line that is defined via a start and an end point)
        * In the most easy case we just have to map an interface to another without calculations

## Common Use Cases
+ Most of the time a simple adapter is inefficient since it creates some temporary objects.
    - Then, we can implement a caching adapter that saves already calculated adapted instances and returns them if they are already exist
    - This is done by a static member and a hash map in most cases, see caching adapter as an example