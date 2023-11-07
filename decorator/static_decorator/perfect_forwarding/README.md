# Perfect Forwarding
+ Perfect forwarding is a technique that enables us to forward arguments to underlying functions/methods/constructors while preserving their rvalue or lvalue property
+ It is mostly used in combination with templates and generic programming

## Implementation details
+ If you have a method/function with `&&` as parameter, this normally means that you want to enforce rvalues as parameters
    - There is the special case for perfect forwarding where we need to use the `&&` reference for the perfect forwarding arguments as well