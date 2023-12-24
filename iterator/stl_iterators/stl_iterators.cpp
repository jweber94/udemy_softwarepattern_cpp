#include <iostream>
#include <vector>
#include <string>

int main() {
	std::vector<std::string> names{ "john", "jane", "jill", "jack" };
	std::vector<std::string>::iterator it = names.begin(); // could also be accessed by std::begin(names)
		// We can have a vector iterator explicitly
	
	// follow the iterator
	std::cout << "name = " << *it << std::endl; // the dereferencing iterator gives us access to the underlying datastructure. The backend of the iterator is mostly a pointer but it does not need to be a pointer. The * operator is overloaded for the iterator type
	
	it++; // The ++ operator (as well as the -- operator) is overloaded to be able to traverse the underlying datastructure easily

	it->append(" godall"); // also the -> operator is overloaded to access the methods of the underlying datastructure. (Even if the iterator does not work on a pointer, it is always accessed via the -> operator to indicate that we want to access the iterator referenced object)
		// so we can modify the underyling object behind an iterator if the iterator is not marked as const	
	
	const std::vector<std::string>::iterator test = names.begin();
	// test++; // does not work since the const tells the compiler that the iterator object test is not able to reference another element of our datastructure then the initially assigned names.begin() iterator
	test->append(" bar");
	std::cout << "test is " << *test << std::endl;

	std::vector<std::string>::const_iterator test2 = names.begin();
	test2++; // this is possible since the const_iterator object is variable with regard to the object that it is pointing to but the underyling object is immutable via the const_iterator object
	// test2->append(" bar"); // does not work because the underlying object is immutable

	// names.end() is the pointer after the last element in our datastructure
	// 0 1 2 3		- this is the iterator indexing
	//         ^	- this is the position of names.end()
	while (++it != names.end()) { // the first time that the iterator is out of bound of the underyling datastructure and iterators a fully countable indexed based objects, this is the termination condition for valid iterator objects
		std::cout << *it << std::endl;
	}

	// rolling iterators from the back to the front
	auto reverseIt = names.rbegin();
	auto reverseTerminationItertor = names.rend();
		//   0 1 2 3	- this is the indexing of names
		// ^			- this is names.rend()

	for (auto ri = std::rbegin(names); ri != std::rend(names); ++ri) {
		std::cout << *ri << std::endl;
	}

	// We can also increment/change the itertor index of the underlying datatstructure with adding numbers (as indices)
	auto it1 = names.begin();
	it1 = it1 + 2;
	std::cout << *it1 << std::endl;

	return 0;
}