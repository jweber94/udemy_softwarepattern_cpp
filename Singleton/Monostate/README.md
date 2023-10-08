# Monostate
+ The Monostate is a defacto singleton:
    - You define all data of a class as static variables and therefor all instances of the class access the same storage (and therefor the same values)
    - That means even if we have a normal class, the data behind our class works as a singleton!
+ If a monostate class is not well documented or the API makes it clear that we have a monostate class, the user of the class will have some crude behaviour if he is not aware of it
+ The Monostate is mostly a very bad code smell!
    - A lot of drawback comes with the monostate if you want to avoid a singleton with it!