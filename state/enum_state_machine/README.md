# Enum State Machine
+ This is a more elaborated approach for handcrafting your state machine. It is much more robust and less error prone then the polymorphic approach that we have seen in the _classical state machine_ example!

## Implementation details
+ In a real world scenario, the main loop of the FSM would be implemented within a class that executes the FSM and the state transition requests would come from another class (e.g. via the observer pattern or from another, concurrently running thread).