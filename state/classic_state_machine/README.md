# Classical approach to state machines
+ This is the vanilla implementation from the gang of four book but it is not recommented to implement it in the real world! There are more sophisticated implementations in libraries like boost, that are much better implemented and tested then doing it on your own.
+ Different paradigm to the modern approach of implementing a state machine!
	- *Do not do this in production, since we can do better today!*

## Implementation Details
+ We use polymophic inheritance to make the state logic work properly