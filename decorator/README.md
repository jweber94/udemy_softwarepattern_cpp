# Decorator Pattern
+ Basic Idea: ***Adding functionallity to classes without adding code to them***
    - But via inheritance strategies
    - Preserve the open close pinciples
    - Preserve single responsability principle
        * The added functionallity might be viewed as a separate concern

## Use Cases
+ You don't have access to the source code of classes that you use in your application or library (or you are not able to add code to them, because they come from a library that is not under your control)

## Implementation approaches
+ We need to interact with the given classes/instances of the classes, e.g. via
    - Aggregation of the base object with a new decorator class
    - Inherit from the decorated object via mixin inheritance