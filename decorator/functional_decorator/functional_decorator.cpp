#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;


struct Logger {
	std::function<void()> _func;
	std::string _name;

	Logger(const std::function<void()>& func, const std::string& name) :
	_func(func),
	_name(name) {}

	void operator()() const {
		std::cout << "Entering " << _name << std::endl;
		_func();
		std::cout << "Exiting " << _name << std::endl;
	}	
};

template <typename Func>
struct Logger2 {
	Func _func;
	std::string _name;

	Logger2(const Func& func, const std::string& name) :
	_func(func),
	_name(name) {}

	void operator()() const {
		std::cout << "Entering " << _name << std::endl;
		_func();
		std::cout << "Exiting " << _name << std::endl;
	}	
};

// to make the Logger2 createabe with type deduction from the compiler, we need to implement a global factroy method to achive this
template <typename Func>
auto make_logger2(Func func, const std::string& name) {
	return Logger2<Func>{func, name};
}

/* Decorate a function with parameters (instead of void void) */
double add(double a, double b) {
	std::cout << a << " + " << b << " = " << (a + b) << std::endl;
	return (a+b); 
}

// partial specialization
template <typename>
struct Logger3;

template <typename R, typename ...Args>
struct Logger3<R(Args...)> {
	std::function<R(Args...)> _func;
	std::string _name;
	
	Logger3(const std::function<R(Args...)>& func, const std::string& name):
	_func(func),
	_name(name)
	{}

	R operator()(Args ...args) {
		std::cout << "Entering " << _name << std::endl;
		R result = _func(args...);
		std::cout << "Exiting " << _name << std::endl;
		return result;
	}
};

template <typename R, typename... Args>
auto make_logger3(R (*func)(Args...), const std::string& name) {
	return Logger3<R(Args...)>(
		std::function<R(Args...)>(func),
		name
	);
}

int main()
{
	// constructor decorator
	Logger([](){std::cout << "Hello1" << std::endl;}, "HelloFunction")();
	// Logger2([](){std::cout << "Hello" << std::endl;}, "HelloFunction")(); // this will not work because the compiler can not deduce the type of the template on its own
	Logger2<std::function<void()>>([](){std::cout << "Hello2" << std::endl;}, "HelloFunction2")();
	
	// factory decorator
	auto log = make_logger2([](){std::cout << "Hello Logger Factory" << std::endl;}, "LoggerFactory");
	log();
	
	// Decorator with decorated function with return values
	auto logged_add = make_logger3(add, "Add");
	auto result = logged_add(1, 2); // invoke the decorated function

	return 0;
 }