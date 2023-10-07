# Dependency Injection to make code that depends on the singleton testable
+ Via dependency injection, we have an interface for handing over the singleton to the application logic that should get unit tested
    - By implementing another singleton or something that acts like the singleton, the application logic can be unit tested (and not just integration tested, like in the first example!)

## What do we learn by doing this?
+ If we really need to use a singleton for whatever reason, the singleton should be abstracted by an abstract interface base class which is then used in the application logic.
    - If we do this, we can exchange the singleton by a dummy implementation in case of the unit test of our application logic.