#include <iostream>
#include <utility>

/* Basic variadic template recursion */
void processArgs() {
    std::cout << "Last argument processed" << std::endl;
}

template <typename Arg, typename... Rest>
void processArgs(Arg arg1, Rest... rest) {
    std::cout << arg1 << std::endl;
    processArgs(rest...); // unpack rest by calling rest... - recursively call process args with variadic templated overloaded function processArgs 
}

/* variadic templates and perfect forwarding */
void procArg(int arg) {
    std::cout << "Processing int " << arg << std::endl; 
}

void procArg(double arg) {
    std::cout << "Processing double " << arg << std::endl;
}

void procArg() {
    std::cout << "Finished recursion with variadic templates and perfect forwarding" << std::endl;
}

template <typename Arg, typename... Rest>
void procArg(Arg&& arg1, Rest&&... restArgs) { // the indicator of perfect forwarding is the &&
    procArg(std::forward<Arg>(arg1)); // process the current argument with the appropriate function
    procArg(std::forward<Rest>(restArgs)...); // recursivly call this function
        // the ... is called pack-expansion - if we handover the argument restArgs to std::forward<Rest>, we apply the preceding expression to each element in the variadic template
}

/* fold expression */
// function that should get applied to all parameters of the parameter pack
template <typename T>
T process(T value) {
    return value * 2;
}

// (left) fold expression to add all processed elements of a parameter pack
template <typename... Args>
auto processAll(Args... args) {
    return (... + process(args));
}

int main() {
    /* variadic template recursion */
    processArgs(1, "Hello", 3.14, "A"); // we can handover an arbitrary number and order of arguments to variadic templates
        // The compiler gets the arguments by type deduction
    processArgs<int, std::string, double>(1, "Hello", 3.14); // version without type deduction
    
    /* variadic templates and perfect forwarding */
    int a = 42;
    double b = 3.14;
    processArgs(a, b, "Hello");
    
    /* fold expression */
    int result = processAll(1, 2, 4, 5);
    std::cout << "result of fold expression with processAll " << result << std::endl;
    return 0;
}