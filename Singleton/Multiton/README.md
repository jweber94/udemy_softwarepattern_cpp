# Multiton
+ A multiton is basically a singleton on which you can choose what (static) member you want to have from it, if you are calling `Multiton::get(key)`!
+ It is a more powerful creational pattern to create multiple instances and access them after their creation via the multiton whenever we need them
    - If a member (of the map in our case) is asked for the first time, it is created within the `get` method

## Usage
+ A multiton is meant to be used only with static accessors - you should not instanciate it!
    - We want access to static members of it!
