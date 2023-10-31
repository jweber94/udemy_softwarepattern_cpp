# Static Decorator
+ We want to eliminate the downside of the dynamic decorator: We want to have access to dervied class members from the class of the decorated object
+ We need to use two techniques from C++ for this:
    - *Mixin inheritance*: The idea behind mixin inheritance is that you can inherit from template arguments - this is unique to C++
    - *Perfect Forwarding*: