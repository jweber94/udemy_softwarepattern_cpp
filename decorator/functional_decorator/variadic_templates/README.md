# Variadic Templates

## Implementation Details
+ Basic syntax:
    - `template<typename ... VTName> void fnc(VTName... args){}`: If the `...` is typed _after_ the (variadic) type definition and _before_ the parameter name, it is the pack-operation of the variadic template
    - `processArgs(args...);`: If the `...` is typed after the parameter name, it is the unpack operation. The arguments get unpacked in the order that is handed over during the function call.
+ Pack-Expansion:
    - As we learned before, we need to unpack the variadic template arguments by typing the variable name of the variadic template and then unpack them by reenacting the `...`
    - We can apply C++ expressions by using the pack expansion operator (`...`) after an operation. E.g.:
        * `procArg(std::forward<Rest>(restArgs)...);` and calling procArg(1, 3.14, "Hello")
        * Expands to:
            - `procArg(std::forward<int>(arg1), std::forward<int>(arg2), std::forward<int>(arg3));`
+ Fold expression:
    - You can use left-fold expressions and right-fold expressions. The difference between them is that:
        * A left-fold expression reads out the unpacked arguments from left to right (aka the first argument that is handed over to the variadic template is processed first)
        * A right-fold expression reads out the unpacked arguments from right to left, so the last argument is processed first
    - Left-fold expression syntax:
        * `(initial op ... args)`:
            - `initial`: Initial value from that the fold expression starts
            - `op`: Operator to connect the values that are handed over
            - `...`: Indicator that shows that we have a fold expression
            - `args`: The parameter pack (currently unpacked)
    - Right-fold expression:
        * `(args ... op initial)` 
            - `initial`: Initial value from that the fold expression starts
            - `op`: Operator to connect the values that are handed over
            - `...`: Indicator that shows that we have a fold expression
            - `args`: The parameter pack (currently unpacked)
    - To apply a function before we connect the values of the parameter pack with `op`, just add a function around the parameter pack name within the fold expression
    
## Common application ideoms
+ Recursivly call a function on the arguments list
    - This is the implementation example in `variadic_templates.cpp`
    - We have one overload of the function is all parameters are unpacked. Besides that, we have the recursive method written by the compiler by using two template arguments: one that should get unpacked and one that is a variadic template that is handed over to the recursivly called function.
+ Perfect forwarding